#pragma once

#include <inttypes.h>
#include "Plant.h"

/// Basic write, just plain bit copy.
template <class T>
void write(char* location, T value) {
    memcpy(location, &value, sizeof(T));
}

/// Writes a Range.
template <class R>
void writeRange(char* location, Range<R> range) {
    write(location, range.min);
    write(location + sizeof(R), range.max);
}

/// Writes BoostParameters.
template <class R>
void writeParams(char* location, BoostParameters<R> params) {
    write(location, params.optimum);
    write(location + sizeof(R), params.amount);
    write(location + sizeof(R) + 4, params.range);
    write(location + sizeof(R) + 8, params.susceptibility);
}

/// Basic read, just bits.
template <class T>
T read(const char* location) {
    return *reinterpret_cast<const T*>(location);
}

/// Reads a Range.
template <class R>
Range<R> readRange(const char* location) {
    Range<R> range;
    range.min = read<R>(location);
    range.max = read<R>(location + sizeof(R));
    return range;
}

/// Reads BoostParameters.
template <class R>
BoostParameters<R> readParams(const char* location) {
    BoostParameters<R> params;
    params.optimum = read<R>(location);
    params.amount = read<float>(location + sizeof(R));
    params.range = read<float>(location + sizeof(R) + 4);
    params.susceptibility = read<float>(location + sizeof(R) + 8);
    return params;
}
