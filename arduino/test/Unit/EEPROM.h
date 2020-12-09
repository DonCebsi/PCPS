#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>

class EEPROMClass {
private:
    size_t size;
    char* mem;

public:
    EEPROMClass(size_t size);
    ~EEPROMClass();

    void write(int, char);
    char read(int);

    template<class T>
    void put(int idx, const T& t) {
        memcpy(mem + idx, &t, sizeof(T));
    }

    template<class T>
    void get(int index, T& t) {
        memcpy(&t, mem + index, sizeof(T));
    }
};
extern EEPROMClass EEPROM;

#endif
