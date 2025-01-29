cmake_minimum_required(VERSION 3.22.1)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(lab3 main.cpp matrix.cpp matrix.h LockFreeQueue.cpp LockFreeQueue.h )
