#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

struct AssertionError : public std::exception {
    const char* info;
    AssertionError(const char* info) : info(info) {}
	const char* what() const throw (){
    	return info;
    }
};

int _TESTS_PASSED = 0;
int _TESTS_FAILED = 0;

#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            throw AssertionError(#condition); \
        } \
    } while(false) \

#define TEST(name, ...) \
void name() { \
    std::string _TEST_NAME = #name; \
    std::cout << "- " << _TEST_NAME << ": "; \
    try { \
        { __VA_ARGS__ } \
        _TESTS_PASSED++; \
        std::cout << "passed" << std::endl; \
    } catch (std::exception& e) { \
        std::cout << "failed at " << e.what() << std::endl; \
        _TESTS_FAILED++; \
    } \
}

#define SUITE(...) \
int main() { \
    auto fns = std::vector<void (*)()>{__VA_ARGS__}; \
    std::cout << "Running test suite." << std::endl; \
    for (auto fn : fns) { \
        (fn)(); \
    } \
    std::cout << "Summary: Passed: " << _TESTS_PASSED << ", Failed: " \
    << _TESTS_FAILED << std::endl; \
}

#endif
