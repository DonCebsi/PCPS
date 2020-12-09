#include <Unit.h>
#include <stdio.h>
#include "Plant.h"
#include "Plant.cpp"

bool aboutEqual(float a, float b, float delta) {
    float r = abs(a-b);
    if (r <= delta) return true;
    return false;
}

TEST(aboutEqualMeta, {
    ASSERT(!aboutEqual(1,2,0.5));
    ASSERT(aboutEqual(1.00,1.01,0.02));
})

TEST(multiplicator, {
    BoostParameters<float> boost = BoostParameters<float>();
    boost.amount = 254;
    boost.range = 0.01;
    boost.optimum = 30;

    ASSERT(aboutEqual(calculateMultiplicator(29.89f,boost),76.34,0.01));
})

TEST(ranger, {
    Range<int> r1 = Range<int>();
    Range<double> r2 = Range<double>();

    r1.min = 1;
    r1.max = 3;

    ASSERT(valueInRange(1,r1));
    ASSERT(valueInRange(3,r1));
    ASSERT(valueInRange(2,r1));
    ASSERT(!valueInRange(0,r1));
    ASSERT(!valueInRange(4,r1));

    r2.min = 0.5;
    r2.max = 1.1;

    ASSERT(valueInRange(0.51,r2));
    ASSERT(!valueInRange(1.11,r2));
})

TEST(limiter, {
    Range<int> r1 = Range<int>();
    Range<double> r2 = Range<double>();

    r1.min = 1;
    r1.max = 3;

    ASSERT(closerLimit(1,r1) == 1);
    ASSERT(closerLimit(3,r1) == 3);
    ASSERT(closerLimit(2,r1) == 1 || closerLimit(2,r1) == 3);
    ASSERT(closerLimit(0,r1) == 1);
    ASSERT(closerLimit(4,r1) == 3);

    r2.min = 0.5;
    r2.max = 1.1;

    ASSERT(aboutEqual(valueInRange(0.51,r2),0.5,0.0001));
    ASSERT(aboutEqual(closerLimit(1.11,r2),1.1,0.0001));
})

TEST(healthSteps, {
    PlantSpec spec(ROSE);
    Plant plant;

    FullMeasurements measurements = FullMeasurements();
    measurements.temperature = SensorValue<float>();
    measurements.moisture = SensorValue<short unsigned int>();
    measurements.humidity = SensorValue<float>();
    measurements.light = SensorValue<short unsigned int>();

    measurements.temperature.trusted = true;
    measurements.moisture.trusted = true;
    measurements.moisture.trusted = true;
    measurements.light.trusted = true;

    measurements.temperature.value = 30; // -> 1.2 boost
    measurements.moisture.value = 20; // -> 1
    measurements.humidity.value = 25; // -> 1.46 boost
    measurements.light.value = 100; // -> 1

    plant.health = 100;
    plant.progress = 0;

    plant.evolve(spec, measurements, 1);
    plant.evolve(spec, measurements, 2);

    ASSERT(aboutEqual(plant.progress, 1.165, 0.05));
    ASSERT(plant.health == 100);

    measurements.light.value = 1010; // 2.71

    plant.evolve(spec, measurements, 3);

    ASSERT(aboutEqual(plant.progress, 1.165 + 1.5925, 0.05));
    ASSERT(plant.health == 100);
})

TEST(damageSteps, {
    PlantSpec spec(ROSE);
    Plant plant;

    FullMeasurements measurements = FullMeasurements();
    measurements.temperature = SensorValue<float>();
    measurements.moisture = SensorValue<short unsigned int>();
    measurements.humidity = SensorValue<float>();
    measurements.light = SensorValue<short unsigned int>();

    measurements.temperature.trusted = true;
    measurements.moisture.trusted = true;
    measurements.moisture.trusted = true;
    measurements.light.trusted = true;

    measurements.temperature.value = 30; // -> 1.2 boost
    measurements.moisture.value = 20; // -> 1
    measurements.humidity.value = 70; // -> damage*2
    measurements.light.value = 100; // -> 1

    //plant.health = 100;
    //plant.progress = 0;

    plant.evolve(spec, measurements, 1);
    plant.evolve(spec, measurements, 2);

    ASSERT(plant.progress == 0);
    ASSERT(aboutEqual(plant.health, 80, 0.0001));

    measurements.humidity.value = 30; // -> ok

    plant.evolve(spec, measurements, 3);

    ASSERT(aboutEqual(plant.progress, 8.3, 0.01));
    ASSERT(aboutEqual(plant.health, 85, 0.0001));
})

SUITE(aboutEqualMeta, multiplicator, ranger, limiter, healthSteps, damageSteps)
