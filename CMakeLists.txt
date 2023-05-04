cmake_minimum_required(VERSION 3.25)
project(PrelimTest)

set(CMAKE_CXX_STANDARD 20)

find_package(libgeotiff CONFIG REQUIRED)

add_executable(PrelimTest main.cpp)