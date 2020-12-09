#include "mockSensors.h"
#include "Arduino.h"
#include "Unit.h"

bool compareFullMeasurements(FullMeasurements* a, FullMeasurements* b) {
	// values
	if (!(a->light.value == b->light.value)) return false;
	if (!(a->moisture.value == b->moisture.value)) return false;
	if (!(a->humidity.value == b->humidity.value)) return false;
	if (!(a->temperature.value == b->temperature.value)) return false;
	if (!(a->water.value == b->water.value)) return false;
	// trusted
	if (!(a->light.trusted == b->light.trusted)) return false;
	if (!(a->moisture.trusted == b->moisture.trusted)) return false;
	if (!(a->humidity.trusted == b->humidity.trusted)) return false;
	if (!(a->temperature.trusted == b->temperature.trusted)) return false;
	if (!(a->water.trusted == b->water.trusted)) return false;

	return true;
}

template<class T>
bool compareValue(T a, T b) {
	return (a == b);
}

bool compareTrusted(bool a, bool b) {
	return (a == b);
}

TEST(test_sensors_light, {
	SensorValue<uint16_t> light_a = mockReadLight(-1);
	SensorValue<uint16_t> light_b = mockReadLight(40001);
	SensorValue<uint16_t> light_c = mockReadLight(0);
	SensorValue<uint16_t> light_d = mockReadLight(40000);
	SensorValue<uint16_t> light_e = mockReadLight(12345);

	ASSERT(compareValue(light_a.value, (uint16_t)-1));
	ASSERT(compareValue(light_b.value, (uint16_t)40001));
	ASSERT(compareValue(light_c.value, (uint16_t)0));
	ASSERT(compareValue(light_d.value, (uint16_t)40000));
	ASSERT(compareValue(light_e.value, (uint16_t)12345));

	ASSERT(compareTrusted(light_a.trusted, false));
	ASSERT(compareTrusted(light_b.trusted, false));
	ASSERT(compareTrusted(light_c.trusted, true));
	ASSERT(compareTrusted(light_d.trusted, true));
	ASSERT(compareTrusted(light_e.trusted, true));
})

TEST(test_sensors_moisture, {
	SensorValue<uint16_t> moisture_a = mockReadMoisture(-1);
	SensorValue<uint16_t> moisture_b = mockReadMoisture(951);
	SensorValue<uint16_t> moisture_c = mockReadMoisture(0);
	SensorValue<uint16_t> moisture_d = mockReadMoisture(950);
	SensorValue<uint16_t> moisture_e = mockReadMoisture(123);
	
	ASSERT(compareValue(moisture_a.value, (uint16_t)-1));
	ASSERT(compareValue(moisture_b.value, (uint16_t)951));
	ASSERT(compareValue(moisture_c.value, (uint16_t)0));
	ASSERT(compareValue(moisture_d.value, (uint16_t)950));
	ASSERT(compareValue(moisture_e.value, (uint16_t)123));

	ASSERT(compareTrusted(moisture_a.trusted, false));
	ASSERT(compareTrusted(moisture_b.trusted, false));
	ASSERT(compareTrusted(moisture_c.trusted, true));
	ASSERT(compareTrusted(moisture_d.trusted, true));
	ASSERT(compareTrusted(moisture_e.trusted, true));
})

TEST(test_sensors_humidity, {
	SensorValue<float> humidity_a = mockReadHumidity(-1.0);
	SensorValue<float> humidity_b = mockReadHumidity(100.0);
	SensorValue<float> humidity_c = mockReadHumidity(5.0);
	SensorValue<float> humidity_d = mockReadHumidity(99.0);
	SensorValue<float> humidity_e = mockReadHumidity(45.5);
	
	ASSERT(compareValue(humidity_a.value, (float)-1.0));
	ASSERT(compareValue(humidity_b.value, (float)100.0));
	ASSERT(compareValue(humidity_c.value, (float)5.0));
	ASSERT(compareValue(humidity_d.value, (float)99.0));
	ASSERT(compareValue(humidity_e.value, (float)45.5));

	ASSERT(compareTrusted(humidity_a.trusted, false));
	ASSERT(compareTrusted(humidity_b.trusted, false));
	ASSERT(compareTrusted(humidity_c.trusted, true));
	ASSERT(compareTrusted(humidity_d.trusted, true));
	ASSERT(compareTrusted(humidity_e.trusted, true));
})

TEST(test_sensors_temperature, {
	SensorValue<float> temperature_a = mockReadTemperature(-41.0);
	SensorValue<float> temperature_b = mockReadTemperature(81.0);
	SensorValue<float> temperature_c = mockReadTemperature(-40.0);
	SensorValue<float> temperature_d = mockReadTemperature(80.0);
	SensorValue<float> temperature_e = mockReadTemperature(24.5);

	ASSERT(compareValue(temperature_a.value, (float)-41.0));
	ASSERT(compareValue(temperature_b.value, (float)81.0));
	ASSERT(compareValue(temperature_c.value, (float)-40));
	ASSERT(compareValue(temperature_d.value, (float)80));
	ASSERT(compareValue(temperature_e.value, (float)24.5));
	
	ASSERT(compareTrusted(temperature_a.trusted, false));
	ASSERT(compareTrusted(temperature_b.trusted, false));
	ASSERT(compareTrusted(temperature_c.trusted, true));
	ASSERT(compareTrusted(temperature_d.trusted, true));
	ASSERT(compareTrusted(temperature_e.trusted, true));
})

TEST(test_sensors_water, {
	SensorValue<bool> water_a = mockReadWater(true);
	SensorValue<bool> water_b = mockReadWater(false);

	ASSERT(compareValue(water_a.value, true));
	ASSERT(compareValue(water_b.value, false));


	ASSERT(compareTrusted(water_a.trusted, true));
	ASSERT(compareTrusted(water_b.trusted, true));
})

TEST(test_initMeas, {
	FullMeasurements init = mockInitMeasurements();
	FullMeasurements correct = mockTakeMeasurements(INIT_LIG, INIT_MOI, INIT_HUM, INIT_TEM, true);

	ASSERT(compareFullMeasurements(&init, &correct));
})

TEST(test_replaceError_light, {
	FullMeasurements faulty = mockTakeMeasurements((uint16_t) 40001, (uint16_t) 250, (float) 45.0, (float) 25, true);
	FullMeasurements prevMeasure = mockInitMeasurements();
	FullMeasurements correct_result = mockTakeMeasurements(INIT_LIG, (uint16_t)250, (float) 45.0, (float)25, true);
	
	FullMeasurements replaceResult = mockReplaceErrorMeasurements(&faulty, &prevMeasure);

	ASSERT(compareFullMeasurements(&replaceResult, &correct_result));
})

TEST(test_replaceError_moisture, {
	FullMeasurements faulty = mockTakeMeasurements((uint16_t) 2000, (uint16_t) 1000, (float) 45.0, (float) 25, true);
	FullMeasurements prevMeasure = mockInitMeasurements();
	FullMeasurements correct_result = mockTakeMeasurements((uint16_t) 2000, INIT_MOI, (float) 45.0, (float)25, true);
	
	FullMeasurements replaceResult = mockReplaceErrorMeasurements(&faulty, &prevMeasure);

	ASSERT(compareFullMeasurements(&replaceResult, &correct_result));
})

TEST(test_replaceError_humidity, {
	FullMeasurements faulty = mockTakeMeasurements((uint16_t) 2000, (uint16_t) 250, (float) 0.0, (float) 25, true);
	FullMeasurements prevMeasure = mockInitMeasurements();
	FullMeasurements correct_result = mockTakeMeasurements((uint16_t) 2000, (uint16_t) 250, INIT_HUM, (float)25, true);
	
	FullMeasurements replaceResult = mockReplaceErrorMeasurements(&faulty, &prevMeasure);

	ASSERT(compareFullMeasurements(&replaceResult, &correct_result));
})

TEST(test_replaceError_temperature, {
	FullMeasurements faulty = mockTakeMeasurements((uint16_t) 2000, (uint16_t) 250, (float) 45.0, (float) 100, true);
	FullMeasurements prevMeasure = mockInitMeasurements();
	FullMeasurements correct_result = mockTakeMeasurements((uint16_t) 2000, (uint16_t) 250, (float) 45.0, INIT_TEM, true);
	
	FullMeasurements replaceResult = mockReplaceErrorMeasurements(&faulty, &prevMeasure);

	ASSERT(compareFullMeasurements(&replaceResult, &correct_result));
})

Suite(test_sensors_light, test_sensors_moisture, test_sensors_humidity, test_sensors_temperature, test_sensors_water, test_initMeas, test_replaceError_light, test_replaceError_moisture, test_replaceError_humidity, test_replaceError_temperature)


