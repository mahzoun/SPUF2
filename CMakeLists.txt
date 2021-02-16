cmake_minimum_required(VERSION 3.15)
project(SPUF2)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPUF2 main.cpp PUF.cpp PUF.h utils.cpp utils.h)