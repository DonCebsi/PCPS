#pragma once

#include <inttypes.h>
#define INIT_TEM 20
#define INIT_LIG 20000
#define INIT_HUM 30.0
#define INIT_MOI 300


/// One sensor value together with a bool whether it's trusted.
template<class T>
struct SensorValue {
	T value;
	bool trusted;
};

/// One set of all sensor values with trust flag.
struct FullMeasurements {
	SensorValue<uint16_t> light;
	SensorValue<uint16_t> moisture;
	SensorValue<float> humidity;
	SensorValue<float> temperature;
	SensorValue<bool> water;
};

/// Initializes everything needed to read the sensors.
void setupSensors();

/// Reads all sensors.
FullMeasurements takeMeasurements();

/// Reads the lux value.
/// Range: 0 - 40000 Lux
SensorValue<uint16_t> readLight();

/// Reads the current moisture.
/// Range: 0 - 950
SensorValue<uint16_t> readMoisture();

/// Reads the current humidity.
/// Range: 5% - 99%
SensorValue<float> readHumidity();

/// Reads the current temperature.
/// Range: -40 - 80 °C
SensorValue<float> readTemperature();

/// Reads whether there is water on the sensor.
/// Range: True or False
SensorValue<bool> readWater();

/// Reads the rotary sensor.
int readRotarySensor();

/// Reads current time.
/// Returns a UNIX timestamp.
uint32_t getTime();

/// Adjusts the RTC from unix timestamp.
void setTime(uint32_t unixtime);

/// creates a proxy Measurements
FullMeasurements initMeasurements();

/// replaces untrusted Values with previous trusted Values
void replaceErrorMeasurements(FullMeasurements* newMeasurements, FullMeasurements* prevMeasurements);