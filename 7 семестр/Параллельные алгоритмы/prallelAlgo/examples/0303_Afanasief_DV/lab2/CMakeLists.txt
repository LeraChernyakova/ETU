cmake_minimum_required(VERSION 3.26)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2
        model/Matrix.cpp
        model/MultiplicationMatrix.cpp
        task2_2/ThreadSafeQueue.h
        main.cpp
        model/Flows.cpp
        model/Flows.h
)
find_package(Threads REQUIRED)
target_link_libraries(lab2 PRIVATE Threads::Threads)
