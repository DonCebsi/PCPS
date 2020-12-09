#include <Unit.h>
#include "Serialize.h"

unsigned int i(char c) {
    return (unsigned int)((unsigned char)c);
}

bool aboutEqual(float a, float b, float delta = 0.1) {
    return abs(a-b) <= delta;
}

TEST(test_char, {
    char buffer[1];
    write(buffer, 'a');
    ASSERT(buffer[0] == 'a');
})

TEST(test_int, {
    char buffer[4];
    write(buffer, 10123957);

    ASSERT(i(buffer[0]) == 181);
    ASSERT(i(buffer[1]) == 122);
    ASSERT(i(buffer[2]) == 154);
    ASSERT(i(buffer[3]) == 0);
})

TEST(test_float, {
    char buffer[4];
    write(buffer, 29.2f);

    float r = read<float>(buffer);

    ASSERT(aboutEqual(r, 29.2f));
})

SUITE(test_char, test_int, test_float)
