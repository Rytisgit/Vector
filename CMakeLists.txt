cmake_minimum_required(VERSION 3.9.6)
project(untitled1)
set(GCC_COVERAGE_COMPILE_FLAGS "-O3")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp Vector.h)