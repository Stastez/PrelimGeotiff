cmake_minimum_required(VERSION 3.25)
project(PrelimTest)

set(CMAKE_CXX_STANDARD 20)

find_package(GDAL CONFIG REQUIRED)

add_executable(PrelimTest main.cpp)

target_link_libraries(PrelimTest PRIVATE GDAL::GDAL)