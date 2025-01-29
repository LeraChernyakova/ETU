cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(lab3
        model/Matrix.cpp
        model/MultiplicationMatrix.cpp
        main.cpp
        model/Flows.cpp
        model/Flows.h
        queue/queue.h
)
find_package(Threads REQUIRED)
target_link_libraries(lab3 PRIVATE Threads::Threads)
target_link_libraries(lab3 PRIVATE atomic)
