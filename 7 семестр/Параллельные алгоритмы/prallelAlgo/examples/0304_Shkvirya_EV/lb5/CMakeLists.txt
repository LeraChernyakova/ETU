cmake_minimum_required(VERSION 3.26)
project(lb5)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCL REQUIRED)

add_executable(lb5 main.cpp ppmHelper.hpp opencl/opencl.hpp
        opencl/assert_cl.cpp opencl/assert_cl.h
)

target_link_libraries(lb5 OpenCL::OpenCL)