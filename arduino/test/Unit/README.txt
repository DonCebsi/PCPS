This directory gives you a minimal Arduino unit testing base.

It consists of
 - Unit.h: A header only minimal unit testing framework
 - Arduino.h and other header files: Define a subset of the whole arduino header set
 - Arduino.cpp: Fake implementation of arduino headers

This collection of arduino header files and their respective fake implementations
is by no means complete nor does it want to be, it shall just work with our code.

If you use new features of the arduino environment in your code,
please add them here so the tests continue to work.
