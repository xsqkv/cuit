#!/bin/bash

#PREPARING

SRC_LIB_PATH="src/lib"
SRC_TESTS_PATH="src/tests"

DST_LIB_PATH="build/lib"
DST_TESTS_PATH="build/tests"

LIBS=$(ls src/lib); # GETTING LIBS IN *.h FORMAT
TESTS=$(ls src/tests) # GETTING TESTS IN *.cpp FORMAT

#CHECKING DIRS

if [ ! -d "build" ]; then mkdir build; fi
if [ ! -d "build/tests" ]; then mkdir build/tests; fi
if [ ! -d "build/lib" ]; then mkdir build/lib; fi
if [ ! -d "build/lib/so" ]; then mkdir build/lib/so; fi
if [ ! -d "build/lib/a" ]; then mkdir build/lib/a; fi

for i in $TESTS; do
    time\
    clang++\
    -std=c++20\
    -O3\
    $SRC_TESTS_PATH/$TESTS\
    -o\
    $DST_TESTS_PATH/$TESTS\
    || printf "\e[01;38;05;1m%s\n\n" "Errors!"\
    || printf "\e[01;38;05;10m%s\n\n" "Success Compiling!";
done

exit 0;

#COMPILING TESTS
time\
    clang++\
    -std=c++20\
    -O3\
    $tests\
    -o ../../build/tests/\
    || printf "\e[01;38;05;1m%s\n\n" "Errors!"\
    || printf "\e[01;38;05;10m%s\n\n" "Success Compiling!";

#COMPILING LIBS
    #COMPILING .so FILES

    #COMPILING .a FILES