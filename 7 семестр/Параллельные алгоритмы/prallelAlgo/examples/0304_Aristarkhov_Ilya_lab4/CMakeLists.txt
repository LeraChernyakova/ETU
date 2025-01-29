cmake_minimum_required(VERSION 3.26)
project(0304_Aristarkhov_Ilya_lab4)

set(CMAKE_CXX_STANDARD 23)

add_executable(0304_Aristarkhov_Ilya_lab4 main.cpp
        model/Square_matrix.h
        model/Square_matrix.cpp
        thread/Matrix_threading.h
        thread/Matrix_threading.cpp)
