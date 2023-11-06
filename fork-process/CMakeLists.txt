cmake_minimum_required(VERSION 3.22)
project(fork-process)

set(CMAKE_CXX_STANDARD 14)

add_executable(fork-process src/swapParents.cpp src/timeAlarm.cpp src/signalСut.cpp)

