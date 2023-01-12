#!/bin/bash

tests=$(ls src/tests);

cd src/tests;

time\
    clang++\
    -std=c++2b\
    -O3\
    $tests\
    -o ../../build/tests/\
    ||\
    printf "\e[01;38;05;1m%s\n" "Errors!"\
    ||\
    printf "\e[01;38;05;10m%s\n" "Success Compiling!";