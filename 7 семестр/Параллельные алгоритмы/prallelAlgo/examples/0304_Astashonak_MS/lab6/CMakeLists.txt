cmake_minimum_required(VERSION 3.26)
project(lab6)

find_package(OpenCL REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab6 main.cpp
        engine.h
        utilities/utils.h
        matrix.h
        threading.h)
target_link_libraries(lab6 OpenCL::OpenCL)