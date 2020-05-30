cmake_minimum_required(VERSION 3.16)
project(rational_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(rational_cpp main.cpp rational.hpp rational.cpp exception.hpp numberFormat.cpp numberFormat.hpp)