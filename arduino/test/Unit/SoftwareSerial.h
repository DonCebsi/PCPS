#ifndef SOFTWARESerialClass_H
#define SOFTWARESerialClass_H

#include "Serial.h"

class SoftwareSerial : public SerialClass {
public:
    SoftwareSerial(int, int);
};

#endif
