cmake_minimum_required(VERSION 3.5)
project(6771assign3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h test.cpp test.h)
add_executable(6771assign3 ${SOURCE_FILES})