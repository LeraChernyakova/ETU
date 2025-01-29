cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(sources
        matrix.cpp
        matrix.h
        matrix_process.cpp
        matrix_process.h
        LockFreeQueue.h)

add_executable(main main.cpp ${sources})