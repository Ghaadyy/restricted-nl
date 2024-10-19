cmake_minimum_required(VERSION 3.29)
project(restricted_nl)

set(CMAKE_CXX_STANDARD 20)

add_executable(restricted_nl main.cpp
        src/scanner.cpp
        src/scanner.h
        src/parser.cpp
        src/parser.h
        src/codegen/codegen.h
        src/codegen/selenium.h
        src/codegen/selenium.cpp)

add_library(restricted_nl_lib SHARED
        src/parser.cpp
        src/parser.h
        src/scanner.cpp
        src/scanner.h
        src/codegen/codegen.h
        src/codegen/selenium.h
        src/codegen/selenium.cpp)