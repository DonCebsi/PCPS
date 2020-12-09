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
// void setupSensors();

/// Reads all sensors.
FullMeasurements mockTakeMeasurements(uint16_t light, uint16_t moisture, float humidity, float temperature, bool water);

/// Reads the lux value.
/// Range: 0 - 40000 Lux
SensorValue<uint16_t> mockReadLight(uint16_t value);

/// Reads the current moisture.
/// Range: 0 - 950
SensorValue<uint16_t> mockReadMoisture(uint16_t value);

/// Reads the current humidity.
/// Range: 5% - 99%
SensorValue<float> mockReadHumidity(float value);

/// Reads the current temperature.
/// Range: -40 - 80 °C
SensorValue<float> mockReadTemperature(float value);

/// Reads whether there is water on the sensor.
/// Range: True or False
SensorValue<bool> mockReadWater(bool value);

/// Reads current time.
/// Returns a UNIX timestamp.
uint32_t mockGetTime(uint32_t time);

/// creates a proxy Measurements
FullMeasurements mockInitMeasurements();

/// replaces untrusted Values with previous trusted Values
FullMeasurements mockReplaceErrorMeasurements(FullMeasurements* newMeasurements, FullMeasurements* prevMeasurements);