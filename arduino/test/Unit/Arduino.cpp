#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Wire.h"
#include "Print.h"
#include "EEPROM.h"

void* memcpy_P(void* destination, const void* source, size_t num) {
    memcpy(destination, source, num);
}
unsigned long millis(void) { return 0; }
unsigned long micros(void) { return 0; }
void delay(unsigned long) {}
void delayMicroseconds(unsigned long) {}
void pinMode(uint8_t, uint8_t) {}
void digitalWrite(uint8_t, uint8_t) {}
int digitalRead(uint8_t) { return 0; }
int analogRead(uint8_t) { return 0; }
void analogReference(uint8_t mode) {}
void analogWrite(uint8_t, int) {}
char pgm_read_byte_near(const void* mem_addr) { return 0; }
char pgm_read_byte(const void* mem_addr) { return 0; }

size_t Print::write(const uint8_t *buffer, size_t size) { return 0; }
size_t Print::write(uint8_t) { return 0; }
size_t Print::print(const char*) { return 0; }
size_t Print::print(char) { return 0; }
size_t Print::print(unsigned char) { return 0; }
size_t Print::print(int) { return 0; }
size_t Print::print(unsigned int) { return 0; }
size_t Print::print(long) { return 0; }
size_t Print::print(unsigned long) { return 0; }
size_t Print::print(double, int) { return 0; }
size_t Print::println(const char*) { return 0; }
size_t Print::println(char) { return 0; }
size_t Print::println(unsigned char) { return 0; }
size_t Print::println(int) { return 0; }
size_t Print::println(unsigned int) { return 0; }
size_t Print::println(long) { return 0; }
size_t Print::println(unsigned long) { return 0; }
size_t Print::println(double, int) { return 0; }

int           Stream::available() { return 0; }
int           Stream::read() { return 0; }
int           Stream::peek() { return 0; }
void          Stream::flush() {}
void          Stream::setTimeout(unsigned long timeout) {}
unsigned long Stream::getTimeout(void) { return 0; }
bool          Stream::find(char *target) { return false; }
bool          Stream::find(char *target, size_t length) { return false; }
bool          Stream::findUntil(char *target, char *terminator) { return false; }
bool          Stream::findUntil(char *target, size_t targetLen, char *terminate, size_t termLen) { return false; }
size_t        Stream::readBytes(char *buffer, size_t length) { return 0; }
size_t        Stream::readBytesUntil(char terminator, char *buffer, size_t length) { return 0; }

void     SerialClass::begin() {}
void     SerialClass::begin(unsigned long) {}
void     SerialClass::begin(unsigned long, uint8_t) {}
void     SerialClass::end(void) {}
size_t   SerialClass::write(char) { return 0; }
size_t   SerialClass::write(const char*, size_t) { return 0; }
SerialClass Serial;

SoftwareSerial::SoftwareSerial(int, int) {}

void    WireClass::setClock(uint32_t) {}
void    WireClass::setClockStretchLimit(uint32_t) {}
void    WireClass::beginTransmission(uint8_t) {}
void    WireClass::beginTransmission(int) {}
uint8_t WireClass::endTransmission(void) { return 0; }
uint8_t WireClass::endTransmission(uint8_t) { return 0; }
size_t  WireClass::requestFrom(uint8_t address, size_t size, bool sendStop) { return 0; }
uint8_t WireClass::status() { return 0; }
uint8_t WireClass::requestFrom(uint8_t, uint8_t) { return 0; }
uint8_t WireClass::requestFrom(uint8_t, uint8_t, uint8_t) { return 0; }
uint8_t WireClass::requestFrom(int, int) { return 0; }
uint8_t WireClass::requestFrom(int, int, int) { return 0; }
void    WireClass::onReceive( void (*)(int) ) {}
void    WireClass::onRequest( void (*)(void) ) {}
void    WireClass::send(uint8_t) {}
uint8_t WireClass::receive() {}
WireClass Wire;

EEPROMClass::EEPROMClass(size_t size) : size(size) {
    this->mem = new char[size];
}
EEPROMClass::~EEPROMClass() {
    delete[] this->mem;
};
void EEPROMClass::write(int pos, char value) {
    mem[pos] = value;
}
char EEPROMClass::read(int pos) {
    return mem[pos];
}

EEPROMClass EEPROM(E2END);
