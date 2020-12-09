#include <Arduino.h>
#include <EEPROM.h>

#include "Sensors.h"
#include "Communication.h"
#include "Display.h"
#include "Plant.h"
#include "Memory.h"

///////////////////////////////////////////////////////////////////////////////
/// Communicator with default id = 1. Set to 0 for other arduino before pushing.
const int ARDUINO_ID = 1;

/// Communicator.
Communicator communicator(ARDUINO_ID);

/// Archive starts at EEPROM location 0 and takes up the whole EEPROM.
Archive archive(0, EEPROM.length());

/// Display handle.
Display display;

/// Global plant state.
Plant plant;
PlantSpec spec(ROSE);

/// Connection state.
uint32_t lastPing = -1;

/// Iteration counter.
int iter = 0;

/// Rotary position on last reset
int rotaryReset;

/// remember previous Measurement
FullMeasurements prevMeasure;

/// Stores or sends the sensor values.
void sendOrStoreValues(const FullMeasurements& measurements, bool connected);

/// Handles incommunicatoring messages.
void handleIncomingMessages();

/// Cleans the EEPROM and resets the plant.
void resetPlant();

///////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(9600);

    setupSensors();
    display.setup();
    prevMeasure = initMeasurements();
    rotaryReset = readRotarySensor() > 512 ? 1022 : 0;

    // Read plant and spec that may be in EEPROM
    archive.retrievePlant(plant);
    archive.retrieveSpec(spec);

    delay(5);
}

void loop() {
    // Read sensors
    FullMeasurements measurements = takeMeasurements();
    replaceErrorMeasurements(&measurements, &prevMeasure);
    prevMeasure = measurements;

    // Get current time
    uint32_t now = getTime();
    bool connected = now - lastPing < 10;

    // Make one step of the plant, print the current state of the plant
    // and update the image
    plant.evolve(spec, measurements, now);
    display.draw(plant, spec, measurements, connected);

    // Send data and ping to raspberry every 2.5 seconds
    if (iter % 5 == 0) {
        communicator.sendPing();
        sendOrStoreValues(measurements, connected);
    }

    // Receives messages from the raspberry
    handleIncomingMessages();

    // Store current plant status (in case of failure) every 10 seconds
    if (iter % 20 == 0) {
        archive.storePlant(plant);
    }

    // Delete plant if rotary sensor signal received
    int rotary = readRotarySensor();
    if ((rotary <= 2 && rotaryReset >= 1020) || (rotaryReset <= 2 && rotary >= 1020)) {
        rotaryReset = rotary;
        resetPlant();
    } 

    delay(500);
    iter = (iter + 1) % 1000;
}

///////////////////////////////////////////////////////////////////////////////
void sendOrStoreValues(const FullMeasurements& measurements, bool connected) {
    // We are disconnected
    if (!connected) {
        Snapshot snapshot(measurements, plant);
        archive.storeSnapshot(snapshot);
    } 
    
    // We are connected
    else {
        // Send archived data
        if (archive.getCount() > 0) {
            Snapshot s;
            FullMeasurements measurements;
            Plant archivedPlant;

            while (archive.retrieveSnapshot(s)) {
                s.fill(measurements);
                communicator.sendSensorValues(measurements);

                s.fill(archivedPlant);
                communicator.sendState(archivedPlant);
            }
        }

        // Send sensor values to raspbi
        communicator.sendSensorValues(measurements);

        // Send state to raspbi
        communicator.sendState(plant);
    }
}

void handleIncomingMessages() {
    Message message;
    if (communicator.recvMessage(message)) {
        if (message.type == PING) {
            Serial.println("Received ping");

            // Update lastPing to know whether we are connected
            lastPing = getTime();
            setTime(message.timestamp);
        }
        
        else if (message.type == STATE) {
            Serial.println("Received plant state");

            memcpy(&plant, message.payload, sizeof(Plant));
            archive.storePlant(plant);

            Serial.println("Set plant from payload");
        } 
        
        else if (message.type == SPEC) {
            Serial.println("Received specification");

            memcpy(&spec, message.payload, sizeof(PlantSpec));
            archive.storeSpec(spec);

            Serial.println("Set spec from payload");
        } 
        
        else {
            Serial.println("Received unknown message");
        }

        Serial.println();
    }
}

void resetPlant() {
    archive.clear();
    plant = Plant();
    spec = PlantSpec(ROSE);
}
