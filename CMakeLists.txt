cmake_minimum_required(VERSION 4.1)
project(Ferry)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ferry main.cpp
        Ferry.cpp
        Ferry.h
        Controller.cpp
        Controller.h
        Vessel.cpp
        Vessel.h
        Speedboat.cpp
        Speedboat.h)
