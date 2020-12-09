#ifndef SERIAL_H
#define SERIAL_H

#include "Stream.h"

class SerialClass : public Stream {
public:
    void begin();
    void begin(unsigned long);
    void begin(unsigned long, uint8_t);
    void end();
    size_t write(char);
    size_t write(const char*, size_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
};
extern SerialClass Serial;

#endif