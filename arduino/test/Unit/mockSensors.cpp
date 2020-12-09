#include "mockSensors.h"
#include "Wire.h"
// #include <DHT.h>
// #include <RTClib.h>
// #include <Digital_Light_TSL2561.h>


// Ports
// const int P_TEMP_HUMIDITY = A1;
// const int P_MOISTURE = A3;
// const int P_WATER = DD3;
// DHT dht(P_TEMP_HUMIDITY, DHT22);
// RTC_DS1307 RTC;

// void setupSensors() {
	// Wire.begin();
	// TSL2561.init();
	// dht.begin();
	// pinMode(P_WATER, INPUT);
	// RTC.begin();
	// RTC.adjust(DateTime(__DATE__, __TIME__));
// }

FullMeasurements mockTakeMeasurements(uint16_t light, uint16_t moisture, float humidity, float temperature, bool water) {
	FullMeasurements values;
	values.temperature = readTemperature(temperature);
	values.light = readLight(light);
	values.humidity = readHumidity(humidity);
	values.moisture = readMoisture(moisture);
	values.water = readWater(water);

	return values;
}

SensorValue<uint16_t> mockReadLight(uint16_t value) {
	SensorValue<uint16_t> s;
	s.value = value;
	s.trusted = s.value >= 0 && s.value <= 40000;
	return s;
}

SensorValue<uint16_t> mockReadMoisture(uint16_t value) {
	SensorValue<uint16_t> s;
	s.value = value;
	s.trusted = s.value >= 0 && s.value <= 950;
	return s;
}

SensorValue<float> mockReadHumidity(float value) {
	SensorValue<float> s;
	s.value = value;
	s.trusted = s.value >= 5.0 && s.value <= 99.0;
	return s;
}

SensorValue<float> mockReadTemperature(float value) {
	SensorValue<float> s;
	s.value = value;
	s.trusted = s.value >= -40.0 && s.value <= 80.0;
	return s;
}

SensorValue<bool> mockReadWater(bool value) {
	SensorValue<bool> s;
	s.value = value;
	s.trusted = true;
	return s;
}

uint32_t mockGetTime(uint32_t time) {
	return time;
}

FullMeasurements mockInitMeasurements() {
	FullMeasurements values;
	values.temperature.value = INIT_TEM;
	values.temperature.trusted = true;
	values.light.value = INIT_LIG;
	values.light.trusted = true;
	values.humidity.value = INIT_HUM;
	values.humidity.trusted = true;
	values.moisture.value = INIT_MOI;
	values.moisture.trusted = true;
	values.water.value = false;
	values.water.trusted = true;
	return values;
}

FullMeasurements mockReplaceErrorMeasurements(FullMeasurements* newMeasurements, FullMeasurements* prevMeasurements) {
	FullMeasurements res;

	if (!newMeasurements->temperature.trusted) res.temperature = prevMeasurements->temperature;
	else res.temperature = newMeasurements->temperature;

	if (!newMeasurements->light.trusted) res.light = prevMeasurements->light; 
	else res.light = newMeasurements->light;

	if (!newMeasurements->humidity.trusted) res.humidity = prevMeasurements->humidity;
	else res.humidity = newMeasurements->humidity;

	if (!newMeasurements->moisture.trusted) res.moisture = prevMeasurements->moisture;
	else res.moisture = newMeasurements->moisture;

	if (!newMeasurements->water.trusted) res.water = prevMeasurements->water;
	else res.water = newMeasurements->water;

	return res;
}
