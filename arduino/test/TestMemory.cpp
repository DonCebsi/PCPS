#include <Unit.h>

#include <Arduino.h>
#include "Memory.h"


Archive arch(0, E2END + 1);


unsigned int i(char c) {
    return (unsigned int)((unsigned char)c);
}

void retrieveSnapshot(Snapshot& a) {
    a.time = 1000;    
    a.health = 10;    a.progress = 40.0;
    a.light = 1000;   a.moisture = 40;
    a.humidity = 20;  a.temperature = 25;
    a.water = true;
}

void retrieveSnapshots(Snapshot& a, Snapshot& b, Snapshot& m) {
    retrieveSnapshot(a);

    b.time = 2000;
    b.health = 40;    b.progress = 80.0;
    b.light = 1500;   b.moisture = 80;
    b.humidity = 0;   b.temperature = 1;
    b.water = false;

    m.time = 1500;
    m.health = 25;    m.progress = 60.0;
    m.light = 1250;   m.moisture = 60;
    m.humidity = 10;  m.temperature = 13;
    m.water = false;
}

bool compareSnapshots(const Snapshot& a, const Snapshot& b) {
    return  a.time == b.time && a.health == b.health && a.progress == b.progress
         && a.light == b.light && a.moisture == b.moisture && a.humidity == b.humidity
         && a.temperature == b.temperature && a.water == b.water;
}

TEST(store, {
    Snapshot a;
    retrieveSnapshot(a);

    arch.storeSnapshot(a);

    Snapshot b;
    arch.retrieveSnapshot(b);

    ASSERT(compareSnapshots(a, b));
})

TEST(compress_one, {
    Snapshot a, b, m;
    retrieveSnapshots(a, b, m);

    arch.storeSnapshot(a);
    arch.storeSnapshot(b);
    arch.compressMemory();
    
    Snapshot c;
    arch.retrieveSnapshot(c);

    ASSERT(compareSnapshots(c, m));
})

TEST(compress_multiple, {
    Snapshot a, b, m;
    retrieveSnapshots(a, b, m);

    // 21 snapshots stored, last should not be combined
    for (int i = 0; i < 10; i++) {
        arch.storeSnapshot(a);
        arch.storeSnapshot(b);
    }
    arch.storeSnapshot(b);

    arch.compressMemory();

    Snapshot c;
    arch.retrieveSnapshot(c);
    ASSERT(compareSnapshots(b, c));
    for (int i = 0; i < 10; i++) {
        arch.retrieveSnapshot(c);
        ASSERT(compareSnapshots(c, m));
    }
})

TEST(survive, {
    Snapshot a, b, m;
    retrieveSnapshots(a, b, m);

    arch.storeSnapshot(a);
    arch.storeSnapshot(b);
    arch.storeSnapshot(m);

    // Simulate reset
    Archive newArch(0, E2END + 1);

    Snapshot c;
    newArch.retrieveSnapshot(c);
    ASSERT(compareSnapshots(m, c));
    newArch.retrieveSnapshot(c);
    ASSERT(compareSnapshots(b, c));
    newArch.retrieveSnapshot(c);
    ASSERT(compareSnapshots(a, c));
})

SUITE(store, compress_one, compress_multiple, survive)
