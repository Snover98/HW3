cmake_minimum_required(VERSION 3.7)
project(HW3)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        output.cpp
        output.hpp
        scanner.lex
        parser.ypp SymTable.cpp SymTable.h Exceptions.h StructType.cpp StructType.h Node.h)

add_executable(HW3 ${SOURCE_FILES})