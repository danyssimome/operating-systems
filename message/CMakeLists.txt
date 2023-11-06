cmake_minimum_required(VERSION 3.22)
project(message)

set(CMAKE_CXX_STANDARD 14)

add_executable(message src/client.cpp src/server.cpp src/constants.h)

