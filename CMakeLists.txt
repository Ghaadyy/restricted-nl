cmake_minimum_required(VERSION 3.29)
project(restricted_nl)

set(CMAKE_CXX_STANDARD 20)

add_executable(restricted_nl main.cpp
        Scanner.cpp
        Scanner.h
        parser.cpp
        parser.h)

add_library(restricted_nl_lib SHARED
        parser.cpp 
        parser.h 
        Scanner.cpp 
        Scanner.h)