#pragma once

#include <inttypes.h>

#include "Plant.h"
#include "Sensors.h"

/// Stores all important information from one exact point in time.
struct Snapshot {
    uint32_t time;
    uint8_t health;
    float progress;
    uint16_t light;
    uint16_t moisture;
    uint8_t humidity;
    uint8_t temperature;
    bool water;

    /// Creates an empty snapshot with undefined contents.
    Snapshot();

    /// Creates a snapshot from measurements and state.
    Snapshot(const FullMeasurements& measurements, const Plant& state);

    /// Combines with another snapshot by averaging the values.
    void combineWith(const Snapshot& other);

    /// Fills information into a measurements struct.
    void fill(FullMeasurements& measurements);

    /// Fills information into a plant state struct.
    void fill(Plant& state);
};

/// Stores unlimited amount of snapshots into EEPROM.
/// Compresses with loss when needed.
class Archive {
private:
    size_t specExistsPos;
    size_t specPos;
    size_t plantExistsPos;
    size_t plantPos;
    size_t snapshotCountPos;
    size_t snapshotStart;
    size_t snapshotSize;

    bool compressionNeeded();

    void setCount(size_t count);

public:
    /// Creates a new archive. Minimum size in bytes:
    /// 1 + sizeof(Spec) + 1 + sizeof(Plant) + sizeof(size_t)
    Archive(size_t start, size_t size);

    /// Stores the specification.
    void storeSpec(const PlantSpec& spec);

    /// Retrieve the specification.
    bool retrieveSpec(PlantSpec& spec);

    /// Stores the current plant status.
    void storePlant(const Plant& plant);

    /// Retrieve the current plant.
    bool retrievePlant(Plant& plant);

    /// Stores one snapshots at the end of the archive.
    void storeSnapshot(const Snapshot& snapshot);

    /// Retrieves and removes the last snapshot.
    bool retrieveSnapshot(Snapshot& snapshot);

    /// Get the current snapshot count.
    size_t getCount();

    /// Halves the memory used by combining two adjacent sets.
    void compressMemory();

    /// Removes all snapshots.
    void clear();
};
