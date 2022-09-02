cmake_minimum_required(VERSION 3.10)

project(cuit)

add_compile_options(-std=c++20 -O3)

add_executable(test ../src/tests/test.cpp)
