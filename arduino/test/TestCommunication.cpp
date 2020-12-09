#include <Unit.h>
#include "Communication.h"

bool aboutEqual(float a, float b, float delta = 0.1) {
    return abs(a-b) <= delta;
}

unsigned int i(char c) {
    return (unsigned int)((unsigned char)c);
}

TEST(test_ping, {
    Message message = Message(PING, 14, 120589091, nullptr);

    int len;
    char* bytes = message.encodeBytes(len);
    Message decoded = Message(bytes);
    delete[] bytes;

    ASSERT(decoded.type == message.type);
    ASSERT(decoded.id == message.id);
    ASSERT(decoded.timestamp == message.timestamp);
})

TEST(test_state, {
    Plant plant;
    Message message = Message(STATE, 12, 0, (void*)(&plant));

    int len;
    char* bytes = message.encodeBytes(len);
    Message decoded = Message(bytes);
    delete[] bytes;

    ASSERT(decoded.type == message.type);
    ASSERT(decoded.id == message.id);
    ASSERT(decoded.timestamp == message.timestamp);
    ASSERT(plant.progress == ((Plant*)decoded.payload)->progress);
    ASSERT(plant.health == ((Plant*)decoded.payload)->health);
})

TEST(test_sensors, {
    FullMeasurements sensors;
	sensors.water.value = true;
    sensors.light.value = 200;
	sensors.moisture.value = 1000;
	sensors.humidity.value = 79.4f;
	sensors.temperature.value = 29.2f;
    Message message = Message(SENSORS, 12, 0, (void*)(&sensors));

    int len;
    char* bytes = message.encodeBytes(len);
    Message decoded = Message(bytes);
    delete[] bytes;

    ASSERT(decoded.type == message.type);
    ASSERT(decoded.id == message.id);
    ASSERT(decoded.timestamp == message.timestamp);
    ASSERT(sensors.water.value == ((FullMeasurements*)decoded.payload)->water.value);
    ASSERT(sensors.light.value == ((FullMeasurements*)decoded.payload)->light.value);
    ASSERT(sensors.moisture.value == ((FullMeasurements*)decoded.payload)->moisture.value);
    ASSERT(aboutEqual(sensors.humidity.value, ((FullMeasurements*)decoded.payload)->humidity.value));
    ASSERT(aboutEqual(sensors.temperature.value, ((FullMeasurements*)decoded.payload)->temperature.value));
})

TEST(test_spec, {
    PlantSpec spec(ROSE);
    Message message = Message(SPEC, 12, 0, (void*)(&spec));

    int len;
    char* bytes = message.encodeBytes(len);
    Message decoded = Message(bytes);
    delete[] bytes;

    ASSERT(decoded.type == message.type);
    ASSERT(decoded.id == message.id);
    ASSERT(decoded.timestamp == message.timestamp);
    ASSERT(spec.maxSize == ((PlantSpec*)decoded.payload)->maxSize);
    ASSERT(spec.growSpeed == ((PlantSpec*)decoded.payload)->growSpeed);
    ASSERT(spec.regenerationSpeed == ((PlantSpec*)decoded.payload)->regenerationSpeed);
    ASSERT(spec.temperatureRange.min == ((PlantSpec*)decoded.payload)->temperatureRange.min);
    ASSERT(spec.temperatureRange.max == ((PlantSpec*)decoded.payload)->temperatureRange.max);
    ASSERT(spec.temperatureBoost.optimum == ((PlantSpec*)decoded.payload)->temperatureBoost.optimum);
    ASSERT(spec.temperatureBoost.amount == ((PlantSpec*)decoded.payload)->temperatureBoost.amount);
    ASSERT(spec.temperatureBoost.range == ((PlantSpec*)decoded.payload)->temperatureBoost.range);
    ASSERT(spec.temperatureBoost.susceptibility == ((PlantSpec*)decoded.payload)->temperatureBoost.susceptibility);
    ASSERT(spec.moistureThreshold == ((PlantSpec*)decoded.payload)->moistureThreshold);
    ASSERT(spec.moistureStruggleSeconds == ((PlantSpec*)decoded.payload)->moistureStruggleSeconds);
    ASSERT(spec.moistureLackSusceptibility == ((PlantSpec*)decoded.payload)->moistureLackSusceptibility);
    ASSERT(spec.waterCanGetAboveGround == ((PlantSpec*)decoded.payload)->waterCanGetAboveGround);
    ASSERT(spec.humidityRange.min == ((PlantSpec*)decoded.payload)->humidityRange.min);
    ASSERT(spec.humidityRange.max == ((PlantSpec*)decoded.payload)->humidityRange.max);
    ASSERT(spec.humidityBoost.optimum == ((PlantSpec*)decoded.payload)->humidityBoost.optimum);
    ASSERT(spec.humidityBoost.amount == ((PlantSpec*)decoded.payload)->humidityBoost.amount);
    ASSERT(spec.humidityBoost.range == ((PlantSpec*)decoded.payload)->humidityBoost.range);
    ASSERT(spec.humidityBoost.susceptibility == ((PlantSpec*)decoded.payload)->humidityBoost.susceptibility);
    ASSERT(spec.darkMaxSeconds == ((PlantSpec*)decoded.payload)->darkMaxSeconds);
    ASSERT(spec.lightMaxSeconds == ((PlantSpec*)decoded.payload)->lightMaxSeconds);
    ASSERT(spec.darkLightThreshold == ((PlantSpec*)decoded.payload)->darkLightThreshold);
    ASSERT(spec.darkSusceptibility == ((PlantSpec*)decoded.payload)->darkSusceptibility);
    ASSERT(spec.lightBoost.optimum == ((PlantSpec*)decoded.payload)->lightBoost.optimum);
    ASSERT(spec.lightBoost.amount == ((PlantSpec*)decoded.payload)->lightBoost.amount);
    ASSERT(spec.lightBoost.range == ((PlantSpec*)decoded.payload)->lightBoost.range);
    ASSERT(spec.lightBoost.susceptibility == ((PlantSpec*)decoded.payload)->lightBoost.susceptibility);
})

SUITE(test_ping, test_state, test_sensors, test_spec)
