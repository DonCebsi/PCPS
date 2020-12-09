#include <SoftwareSerial.h>

#include "Sensors.h"
#include "Communication.h"
#include "Serialize.h"


unsigned int i(char c) {
    return (unsigned int)((unsigned char)c);
}

/// Serial channel for WiFi communication
SoftwareSerial XBee(5, 6);

Message::Message() {}

Message::Message(MessageType type, uint8_t id, uint32_t timestamp, void* payload)
    : allocatedPayload(false), type(type), id(id), timestamp(timestamp), payload(payload) {}

Message& Message::operator=(Message&& other) {
    if (&other == this)
        return *this;

    this->type = other.type;
    this->id = other.id;
    this->timestamp = other.timestamp;

    // Transfer ownership of payload
    deallocate();
    this->payload = other.payload;
    this->allocatedPayload = other.allocatedPayload;
    other.payload = nullptr;
    other.allocatedPayload = false;

    return *this;
}

Message::Message(const char* data)
    : allocatedPayload(true) {
    // Read header
    this->type = (MessageType)read<uint8_t>(data);
    this->id = read<uint8_t>(data + 1);
    this->timestamp = read<uint32_t>(data + 2);
    this->payload = NULL;

    // Read body
    const char* body = data + HEADER_LEN;
    if (this->type == STATE) {
        Plant* state = new Plant;

        state->progress = read<float>(body);
        state->health = read<float>(body + 4);

        this->payload = state;
    } else if (this->type == SENSORS) {
        FullMeasurements* sensorValues = new FullMeasurements;

        sensorValues->water.value = (bool)read<uint8_t>(body);
        sensorValues->light.value = read<uint16_t>(body + 1);
        sensorValues->moisture.value = read<uint16_t>(body + 3);
        sensorValues->temperature.value = read<float>(body + 5);
        sensorValues->humidity.value = read<float>(body + 9);

        this->payload = sensorValues;
    } else if (this->type == SPEC) {
        PlantSpec* spec = new PlantSpec;

        size_t offset = 0;
        spec->maxSize = read<float>(body + offset);
        spec->growSpeed = read<float>(body + offset + 4);
        spec->regenerationSpeed = read<float>(body + offset + 8);
        offset += 12;

        spec->temperatureRange = readRange<float>(body + offset);
        spec->temperatureBoost = readParams<float>(body + offset + 8);
        offset += 24;

        spec->moistureThreshold = read<uint16_t>(body + offset);
        spec->moistureStruggleSeconds = read<uint32_t>(body + offset + 2);
        spec->moistureLackSusceptibility = read<float>(body + offset + 6);
        spec->waterCanGetAboveGround = (bool)read<uint8_t>(body + offset + 10);
        offset += 11;

        spec->humidityRange = readRange<float>(body + offset);
        spec->humidityBoost = readParams<float>(body + offset + 8);
        offset += 24;

        spec->darkMaxSeconds = read<uint64_t>(body + offset);
        spec->lightMaxSeconds = read<uint64_t>(body + offset + 8);
        spec->darkLightThreshold = read<uint32_t>(body + offset + 16);
        spec->darkSusceptibility = read<float>(body + offset + 20);
        offset += 24;

        spec->lightBoost = readParams<uint16_t>(body + offset);
        offset += 14;

        this->payload = spec;
    }
}

char* Message::encodeBytes(int& len) const {
    len = Message::length(this->type);
    char* data = new char[len];

    // Write header
    write(data, this->type);
    write(data + 1, this->id);
    write(data + 2, this->timestamp);

    // Write body
    char* body = data + HEADER_LEN;
    if (this->type == STATE) {
        Plant* state = (Plant*)this->payload;

        write(body, state->progress);
        write(body + 4, state->health);
    } else if (this->type == SENSORS) {
        FullMeasurements* sensors = (FullMeasurements*)this->payload;

        write(body, sensors->water.value);
        write(body + 1, sensors->light.value);
        write(body + 3, sensors->moisture.value);
        write(body + 5, sensors->temperature.value);
        write(body + 9, sensors->humidity.value);
    } else if (this->type == SPEC) {
        PlantSpec* spec = (PlantSpec*)this->payload;

        size_t offset = 0;
        write(body + offset, spec->maxSize);
        write(body + offset + 4, spec->growSpeed);
        write(body + offset + 8, spec->regenerationSpeed);
        offset += 12;

        writeRange(body + offset, spec->temperatureRange);
        writeParams(body + offset + 8, spec->temperatureBoost);
        offset += 24;

        write(body + offset, spec->moistureThreshold);
        write(body + offset + 2, spec->moistureStruggleSeconds);
        write(body + offset + 6, spec->moistureLackSusceptibility);
        write(body + offset + 10, (char)spec->waterCanGetAboveGround);
        offset += 11;

        writeRange(body + offset, spec->humidityRange);
        writeParams(body + offset + 8, spec->humidityBoost);
        offset += 24;

        write(body + offset, spec->darkMaxSeconds);
        write(body + offset + 8, spec->lightMaxSeconds);
        write(body + offset + 16, spec->darkLightThreshold);
        write(body + offset + 20, spec->darkSusceptibility);
        offset += 24;

        writeParams(body + offset, spec->lightBoost);
        offset += 14;
    }

    return data;
};

void Message::deallocate() {
    if (this->payload != nullptr && allocatedPayload) {
        if (this->type == STATE)
            delete (Plant*)this->payload;
        else if (this->type == SENSORS)
            delete (FullMeasurements*)this->payload;
        else if (this->type == SPEC)
            delete (PlantSpec*)this->payload;
    }
}

Message::~Message() {
    deallocate();
}

const size_t Message::length(MessageType type) {
    if (type == PING || type == NEEDMORE) {
        return HEADER_LEN + 0;
    } else if (type == STATE) {
        return HEADER_LEN + 8;
    } else if (type == SENSORS) {
        return HEADER_LEN + 13;
    } else if (type == SPEC) {
        return HEADER_LEN + 109;
    }

    return -1;
}

Communicator::Communicator(uint8_t id) : id(id) {
    XBee.begin(9600);
    XBee.setTimeout(1000);
}

void Communicator::sendPing() const {
    sendMessage(Message(PING, this->id, getTime(), NULL));
}

void Communicator::sendState(const Plant& state) const {
    sendMessage(Message(STATE, this->id, getTime(), (void*)&state));
}

void Communicator::sendSensorValues(const FullMeasurements& measurements) const {
    sendMessage(Message(SENSORS, this->id, getTime(), (void*)&measurements));
}

void Communicator::sendSpec(const PlantSpec& spec) const {
    sendMessage(Message(SPEC, this->id, getTime(), (void*)&spec));
}

void Communicator::sendNeedMore() const {
    sendMessage(Message(NEEDMORE, this->id, getTime(), NULL));
}

void Communicator::sendMessage(const Message& message) const {
    // Convert message to bytes
    int len;
    char* bytes = message.encodeBytes(len);

    /* {
        Serial.print("Sending: [");
        for (int k = 0; k < len; k++) {
            Serial.print(i(bytes[k]));
            Serial.print(", ");
        }
        Serial.println("\b\b]");
    } */

    // Send bytes over WiFi
    XBee.write(bytes, len);

    // Deallocate
    delete[] bytes;
}

bool Communicator::recvMessage(Message& message) const {
    // Return if no bytes
    if (XBee.available() <= 0)
        return false;

    // Get message type, discard all random stuff coming in
    Serial.print("Reading: [");
    char first;
    do {
        first = XBee.read();
        Serial.print(i(first));
        Serial.print(", ");
    } while (first > MESSAGE_TYPE_MAX);
    Serial.println("\b\b]");

    // We got nothing, after discarding random stuff
    if (first < 0) {
        return false;
    }

    // Find out how long a message of this type is
    int len = Message::length((MessageType)first);

    // Read the remaining len - 1 bytes into a freshly allocated buffer
    char* buffer = new char[len];
    buffer[0] = first;

    Serial.print("Reading message bytes of type ");
    Serial.println(i(first));

    int needMoreCounter = 5;

    // Read bytes while we need more
    Serial.print("Reading: [");
    int bytesRead = 1;
    while (bytesRead < len) {
        if (needMoreCounter <= 0) {
            delete[] buffer;
            return false;
        } else if (XBee.available() > 0) {
            // Read one byte
            char read = XBee.read();
            Serial.print(i(read));
            Serial.print(", ");
            buffer[bytesRead] = read;
            bytesRead++;
        } else {
            // Request more bytes from raspi
            Serial.println("..., ");
            sendNeedMore();
            needMoreCounter--;
            delay(1000);
        }
    }
    Serial.println("\b\b]");

    Serial.print("Parsing bytes ... ");

    // Set the message for the caller
    message = Message(buffer);

    Serial.println("finished");

    delete[] buffer;
    return true;
}
