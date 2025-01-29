cmake_minimum_required(VERSION 3.16.3)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

SET(MYCOMPILE_FLAGS "-pthread")

add_definitions(${MYCOMPILE_FLAGS})

add_executable(lab3 main.cpp
        Utils.hpp
        LockFreeQueue.hpp
)
