cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)

set(CMAKE_C_FLAGS "-std=c++11 -Wall -DNDEBUG")
add_executable(avl main1.cpp library.cpp boom.cpp)