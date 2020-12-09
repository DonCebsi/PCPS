#ifndef WIRE_H
#define WIRE_H

#include "Serial.h"

class WireClass : public SerialClass {
public:
    void setClock(uint32_t);
    void setClockStretchLimit(uint32_t);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission();
    uint8_t endTransmission(uint8_t);
    size_t requestFrom(uint8_t address, size_t size, bool sendStop);
	uint8_t status();
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    void onReceive( void (*)(int) );
    void onRequest( void (*)() );
    void send(uint8_t);
    uint8_t receive();
};
extern WireClass Wire;

#endif
