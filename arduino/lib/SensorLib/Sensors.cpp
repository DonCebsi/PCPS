#include "Sensors.h"
#include <Wire.h>
#include <DHT.h>
#include <Digital_Light_TSL2561.h>
#include <RTClib.h>


// Ports
const int P_ROTARY_ANGLE = A0;
const int P_TEMP_HUMIDITY = A1;
const int P_MOISTURE = A3;
const int P_WATER = DD3;
DHT dht(P_TEMP_HUMIDITY, DHT22);
RTC_DS1307 RTC;

void setupSensors() {
	Wire.begin();
	TSL2561.init();
	dht.begin();
	pinMode(P_WATER, INPUT);
	pinMode(P_ROTARY_ANGLE, INPUT);
	RTC.begin();
	RTC.adjust(DateTime(__DATE__, __TIME__));
}

FullMeasurements takeMeasurements() {
	FullMeasurements values;
	values.temperature = readTemperature();
	values.light = readLight();
	values.humidity = readHumidity();
	values.moisture = readMoisture();
	values.water = readWater();

	return values;
}

SensorValue<uint16_t> readLight() {
	SensorValue<uint16_t> s;
	s.value = TSL2561.readVisibleLux();
	s.trusted = s.value >= 0 && s.value <= 40000;
	return s;
}

SensorValue<uint16_t> readMoisture() {
	SensorValue<uint16_t> s;
	s.value = analogRead(P_MOISTURE);
	s.trusted = s.value >= 0 && s.value <= 950;
	return s;
}

SensorValue<float> readHumidity() {
	SensorValue<float> s;
	s.value = dht.readHumidity();
	s.trusted = s.value >= 5.0 && s.value <= 99.0;
	return s;
}

SensorValue<float> readTemperature() {
	SensorValue<float> s;
	s.value = dht.readTemperature();
	s.trusted = s.value >= -40.0 && s.value <= 80.0;
	return s;
}

SensorValue<bool> readWater() {
	SensorValue<bool> s;
	s.value = digitalRead(P_WATER) == LOW;
	s.trusted = true;
	return s;
}

int readRotarySensor() {
	return analogRead(P_ROTARY_ANGLE);
}

uint32_t getTime() {
	DateTime now = RTC.now();
	return now.unixtime();
}

void setTime(uint32_t unixtime) {
	DateTime now(unixtime);
	RTC.adjust(now);
}

FullMeasurements initMeasurements() {
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

void replaceErrorMeasurements(FullMeasurements* newMeasurements, FullMeasurements* prevMeasurements) {
	if (!newMeasurements->temperature.trusted) {
		newMeasurements->temperature = prevMeasurements->temperature;
	}
	if (!newMeasurements->light.trusted) {
		newMeasurements->light = prevMeasurements->light;
	}
	if (!newMeasurements->humidity.trusted) {
		newMeasurements->humidity = prevMeasurements->humidity;
	}
	if (!newMeasurements->moisture.trusted) {
		newMeasurements->moisture = prevMeasurements->moisture;
	}
	if (!newMeasurements->water.trusted) {
		newMeasurements->water = prevMeasurements->water;
	}
}
