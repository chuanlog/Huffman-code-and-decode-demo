cmake_minimum_required(VERSION 3.28)
project(Code)

set(CMAKE_CXX_STANDARD 17)

add_executable(Code main.cpp
        huffmanCode.h
        huffmanTreeNode.h
        txtFileFunctions.h
        Timer.cpp
        Timer.h)
