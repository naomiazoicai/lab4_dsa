cmake_minimum_required(VERSION 3.24)
project(lab4_dsa)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab4_dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h)
