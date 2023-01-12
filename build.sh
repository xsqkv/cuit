#!/bin/bash

#PREPARING
SRC_LIB_PATH="src/lib" # SOURCE LIB PATH
SRC_TESTS_PATH="src/tests" # SOURCE TESTS PATH

DST_LIB_PATH="build/lib" # LIB PATH DESTINATION
DST_TESTS_PATH="build/tests" # TESTS PATH DESTINATION

LIBS=$(ls src/lib); # GETTING LIBS IN *.h FORMAT
TESTS=$(ls src/tests) # GETTING TESTS IN *.cpp FORMAT

function check_dirs()
{
    # CHECKING DIRS
    if [ ! -d "build" ]; then mkdir build; fi # CHECKING build FOLDER
    if [ ! -d "build/tests" ]; then mkdir build/tests; fi # CHECKING build/tests FOLDER
    if [ ! -d "build/lib" ]; then mkdir build/lib; fi # CHECKING build/lib FOLDER
    if [ ! -d "build/lib/so" ]; then mkdir build/lib/so; fi # CHECKING build/lib/so FOLDER
    if [ ! -d "build/lib/a" ]; then mkdir build/lib/a; fi # CHECKING build/lib/a FOLDER
}

function compile_tests()
{
    # COMPILING TESTS
    for FILE in $TESTS;
    do
        echo building "$SRC_TESTS_PATH/$FILE"
        clang++\
            -std=c++20\
            -O3\
            "$SRC_TESTS_PATH/$FILE"\
            -o\
            "$DST_TESTS_PATH/$(basename "$FILE" .cpp)"\
            && printf "\e[01;38;05;10m%s\e[0m\n\n" "Success Compiling!"\
            || printf "\e[01;38;05;1m%s\e[0m\n\n" "An Errors Occurred!"
    done
}

function main() 
{
    check_dirs; # CHECKING DIRS

    compile_tests; # COMPILING TESTS

    # COMPILING LIBS

        # COMPILING .so FILES


        # COMPILING .a FILES
}

time main;