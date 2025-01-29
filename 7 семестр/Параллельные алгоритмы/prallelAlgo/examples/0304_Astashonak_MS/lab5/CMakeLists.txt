cmake_minimum_required(VERSION 3.26)
project(lab5)

find_package(OpenCL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab5 main.cpp
        svpng.h
        assert.h
        engine.h)
target_link_libraries(lab5 OpenCL::OpenCL)