cmake_minimum_required(VERSION 3.22)
project(channels)

set(CMAKE_CXX_STANDARD 23)

add_executable(channels src/server.cpp src/client.cpp src/constants.h)
