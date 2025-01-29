cmake_minimum_required(VERSION 3.26)
project(lb6)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCL REQUIRED)

add_executable(lb6
        opencl/opencl.hpp opencl/assert_cl.cpp opencl/assert_cl.h
        Matrix.hpp Utils.hpp main.cpp
)

target_link_libraries(lb6 OpenCL::OpenCL)