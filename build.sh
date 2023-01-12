#!/bin/bash

time\
    clang++\
    -std=c++2b\
    -O3 src/tests/test.cpp\
    -o build/tests/test