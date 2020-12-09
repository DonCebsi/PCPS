#ifndef STREAM_H
#define STREAM_H

#include "Print.h"

class Stream : public Print {
public:
    int available();
    int read();
    int peek();
    void flush();
    void setTimeout(unsigned long timeout);
    unsigned long getTimeout(void);
    bool find(char *target);
    bool find(char *target, size_t length);
    bool findUntil(char *target, char *terminator);
    bool findUntil(char *target, size_t targetLen, char *terminate, size_t termLen);
    size_t readBytes(char *buffer, size_t length);
    size_t readBytesUntil(char terminator, char *buffer, size_t length);
};

#endif
