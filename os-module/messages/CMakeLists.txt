cmake_minimum_required(VERSION 3.22)
project(messages)

set(CMAKE_CXX_STANDARD 14)

add_executable(messages src/client.cpp src/server.cpp src/constants.h)
