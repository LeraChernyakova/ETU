cmake_minimum_required(VERSION 3.22.1)
project(pthreads)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(pthreads main.cpp threads.cpp threads.h)
