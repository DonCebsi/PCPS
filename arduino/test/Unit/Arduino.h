#ifndef ARDUINO_H
#define ARDUINO_H

#include <inttypes.h>
#include <string>
#include <cmath>
#include <cstddef>
#include <cstring>

#include "Serial.h"

#define E2END 0x3FF
#define PROGMEM
#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define EULER 2.718281828459045235360287471352
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define SERIAL  0x0
#define DISPLAY 0x1
#define LSBFIRST 0
#define MSBFIRST 1
#define CHANGE 1
#define FALLING 2
#define RISING 3

#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define DD1 1
#define DD2 2
#define DD3 3
#define DD4 4

typedef bool boolean;
typedef uint8_t byte;
typedef std::string String;
class __FlashStringHelper;

void* memcpy_P(void* destination, const void* source, size_t num);
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned long);
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);
char pgm_read_byte_near(const void* mem_addr);
char pgm_read_byte(const void* mem_addr);

#endif
