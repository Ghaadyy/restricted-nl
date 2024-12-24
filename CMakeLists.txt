cmake_minimum_required(VERSION 3.10)
project(restricted_nl)

set(CMAKE_CXX_STANDARD 23)

add_executable(restricted_nl main.cpp
        src/scanner.cpp
        src/scanner.h
        src/parser.cpp
        src/parser.h
        src/ast/AST.cpp
        src/ast/AST.h
        src/ast/SeleniumASTVisitor.cpp
        src/ast/SeleniumASTVisitor.h)

add_library(restricted_nl_lib SHARED
        src/parser.cpp
        src/parser.h
        src/scanner.cpp
        src/scanner.h
        src/ast/AST.cpp
        src/ast/AST.h
        src/ast/SeleniumASTVisitor.cpp
        src/ast/SeleniumASTVisitor.h)