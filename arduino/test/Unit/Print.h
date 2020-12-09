#ifndef PRINT_H
#define PRINT_H

#include "Arduino.h"

class Print {
public:
    size_t write(const uint8_t *buffer, size_t size);
    size_t write(uint8_t);

    size_t print(const char*);
    size_t print(char);
    size_t print(unsigned char);
    size_t print(int);
    size_t print(unsigned int);
    size_t print(long);
    size_t print(unsigned long);
    size_t print(double, int);

    size_t println(const char*);
    size_t println(char);
    size_t println(unsigned char);
    size_t println(int);
    size_t println(unsigned int);
    size_t println(long);
    size_t println(unsigned long);
    size_t println(double, int);
};

#endif
