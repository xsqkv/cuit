#!/bin/bash

#PREPARING

source settingsBuild.sh; # READ VARIABLES FROM buildSettings.sh FILE

SRC_LIB_PATH="src/lib"; # SOURCE LIB PATH
SRC_TESTS_PATH="src/tests"; # SOURCE TESTS PATH

DST_TESTS_PATH="build/tests"; # TESTS PATH DESTINATION
DST_OBJ_PATH="build/lib/o"; # OBJECTS PATH DESTINATION
DST_A_PATH="build/lib/a"; # STATIC LIBRARIES PATH DESTINATION
DST_SO_PATH="build/lib/so"; # SHARED OBJECTS PATH DESTINATION

cd src/lib; LIBS=$(ls *.hpp); # GETTING LIBS IN *.hpp FORMAT
cd ..; cd tests; TESTS=$(ls *.cpp); # GETTING TESTS IN *.cpp FORMAT

cd ../../;

function SUCCESS()
{
    printf "\e[01;38;05;10m%s\e[0m\n\n" "Success Compiling!";
}

function ERRORS()
{
    printf "\e[01;38;05;1m%s\e[0m\n\n" "An Errors Occurred!";
}

function compile_tests()
{
    # CHECKING build FOLDER
    if [ ! -d "build" ]; then mkdir build; fi 
    # CHECKING build/tests FOLDER
    if [ ! -d "build/tests" ]; then mkdir build/tests; fi 

    # COMPILING TESTS
    for FILE in $TESTS;
    do
        echo building "$SRC_TESTS_PATH/$FILE";
        $COMPILER $CFLAGS $SRC_TESTS_PATH/$FILE -o "$DST_TESTS_PATH/$(basename $FILE .cpp)"\
            && SUCCESS\
            || ERRORS;
    done
}

function compile_objects()
{
    # CHECKING build/lib FOLDER
    if [ ! -d "build/lib" ]; then mkdir build/lib; fi

    # CHECKING build/lib/o FOLDER
    if [ ! -d "build/lib/o" ]; then mkdir build/lib/o; fi
    
    # COMPILING OBJECTS
    for LIB in $LIBS;
    do
        echo building "$DST_OBJ_PATH/$(basename "$LIB" .hpp).o";
        $COMPILER $CFLAGS "$SRC_LIB_PATH/$LIB" -o "$DST_OBJ_PATH/$(basename $LIB .hpp).o"\
            && SUCCESS\
            || ERRORS;
    done
}

function compile_archives()
{
    # CHECKING build/lib/a FOLDER
    if [ ! -d "build/lib/a" ]; then mkdir build/lib/a; fi 

    # GETTING OBJECTS IN *.o FORMAT
    OBJECTS=$(ls build/lib/o); 

    # COMPILING STATIC LIBRARIES
    for OBJ in $OBJECTS;
    do
        echo building "$DST_A_PATH/$(basename "$OBJ" .o).a";
        $AR $ARFLAGS "$DST_A_PATH/$(basename "$OBJ" .o).a" $DST_OBJ_PATH/$OBJ\
            && SUCCESS\
            || ERRORS;
    done
}

function compile_shared_objects()
{
    # CHECKING build/lib/so FOLDER
    if [ ! -d "build/lib/so" ]; then mkdir build/lib/so; fi

    # COMPILING STATIC LIBRARIES
    for LIB in $LIBS;
    do
        echo "$DST_SO_PATH/$(basename "$LIB" .hpp).so";
        $COMPILER $CFLAGS -shared -o "$DST_SO_PATH/$(basename "$LIB" .hpp).so" $SRC_LIB_PATH/$LIB\
            && SUCCESS\
            || ERRORS;
    done
}

function main() 
{
    compile_tests; # COMPILING TESTS
    #compile_objects; # COMPILING .o FILES
    #compile_archives; # COMPILING .a FILES
    #compile_shared_objects; # COMPILING .so FILES
}

time main;
