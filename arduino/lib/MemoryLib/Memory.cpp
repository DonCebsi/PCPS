#include <Arduino.h>
#include <EEPROM.h>

#include "Sensors.h"
#include "Plant.h"
#include "Memory.h"


Snapshot::Snapshot() {}

Snapshot::Snapshot(const FullMeasurements& measurements, const Plant& state) {
    this->time = getTime();
    this->health = state.health;
    this->progress = state.progress;
    this->light = measurements.light.value;
    this->moisture = measurements.moisture.value;
    this->humidity = measurements.humidity.value;
    this->temperature = (measurements.temperature.value + 40) * 2;
    this->water = measurements.water.value;
}

void Snapshot::fill(FullMeasurements& measurements) {
    measurements.light.value = this->light;
    measurements.moisture.value = this->moisture;
    measurements.humidity.value = this->humidity;
    measurements.temperature.value = this->temperature / 2 - 40;
    measurements.water.value = this->water;
}

void Snapshot::fill(Plant& state) {
    state.health = this->health;
    state.progress = this->progress;
}

void Snapshot::combineWith(const Snapshot& other) {
    time = (time + other.time) / 2;
    health = (health + other.health) / 2;
    progress = (progress + other.progress) / 2;
    light = (light + other.light) / 2;
    moisture = (moisture + other.moisture) / 2;
    humidity = (humidity + other.humidity) / 2;
    temperature = (temperature + other.temperature) / 2;
    water = water && other.water;
}


Archive::Archive(size_t start, size_t size) {
    this->specExistsPos = start;
    this->specPos = this->specExistsPos + sizeof(bool);
    this->plantExistsPos = this->specPos + sizeof(PlantSpec);
    this->plantPos = this->plantExistsPos + sizeof(bool);
    this->snapshotCountPos = this->plantPos + sizeof(Plant);
    this->snapshotStart = this->snapshotCountPos + sizeof(size_t);
    this->snapshotSize = size - (this->snapshotStart - start);
}

void Archive::storeSpec(const PlantSpec& spec) {
    EEPROM.put(this->specPos, spec);
    EEPROM.put(this->specExistsPos, true);
}

bool Archive::retrieveSpec(PlantSpec& spec) {
    bool exists;
    EEPROM.get(this->specExistsPos, exists);
    if (exists) {
        EEPROM.get(this->specPos, spec);
    } 
    return exists;
}

void Archive::storePlant(const Plant& plant) {
    EEPROM.put(this->plantPos, plant);
    EEPROM.put(this->plantExistsPos, true);
}

bool Archive::retrievePlant(Plant& plant) {
    bool exists;
    EEPROM.get(this->plantExistsPos, exists);
    if (exists) {
        EEPROM.get(this->plantPos, plant);
    } 
    return exists;
}

size_t Archive::getCount() {
    size_t count;
    EEPROM.get(this->snapshotCountPos, count);
    return count;
}

void Archive::setCount(size_t count) {
    if (count != getCount())
        EEPROM.put<size_t>(this->snapshotCountPos, count);
}

void Archive::storeSnapshot(const Snapshot& snapshot) {
    if (compressionNeeded()) {
        compressMemory();
    }

    size_t count = getCount();
    EEPROM.put(this->snapshotStart + count * sizeof(Snapshot), snapshot);
    setCount(count + 1);
}

bool Archive::retrieveSnapshot(Snapshot& snapshot) {
    size_t count = getCount();
    if (count <= 0)
        return false;

    EEPROM.get(this->snapshotStart + (count - 1) * sizeof(Snapshot), snapshot);
    setCount(count - 1);

    return true;
}

void Archive::clear() {
    bool exists;

    EEPROM.get(this->specExistsPos, exists);
    if (exists)
        EEPROM.put(this->specExistsPos, false);

    EEPROM.get(this->plantExistsPos, exists);
    if (exists)
        EEPROM.put(this->plantExistsPos, false);

    setCount(0);
}

bool Archive::compressionNeeded() {
    return ((getCount() + 1) * sizeof(Snapshot)) > this->snapshotSize;
}

void Archive::compressMemory() {
    size_t start_count = getCount();
    size_t count = 0;
    for (size_t idx = 0; idx < (start_count + 1) / 2; idx++) {
        Snapshot a, b;
        // Get first value
        size_t fst_idx = 2 * idx;
        EEPROM.get(this->snapshotStart + fst_idx * sizeof(Snapshot), a);

        // If this is not the last value, get a second value and combine them
        size_t snd_idx = 2 * idx + 1;
        if (snd_idx < start_count) {
            EEPROM.get(this->snapshotStart + snd_idx * sizeof(Snapshot), b);
            a.combineWith(b);
        }

        // Store the combined value
        EEPROM.put(this->snapshotStart + idx * sizeof(Snapshot), a);
        count++;
    }
    setCount(count);
}
