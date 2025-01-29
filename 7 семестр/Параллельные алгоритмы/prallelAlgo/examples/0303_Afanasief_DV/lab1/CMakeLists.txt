cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
project(lab1)
add_executable(lab1
        task3/main.cpp
        model/Matrix.cpp
        model/MultiplicationMatrix.cpp)

find_package(Threads REQUIRED)

target_link_libraries(lab1 PRIVATE Threads::Threads)