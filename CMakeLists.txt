cmake_minimum_required(VERSION 3.16)

project(photon)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES src/main.cpp)

add_executable(photon ${SOURCES})