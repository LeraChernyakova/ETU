cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)

project(lab6)

add_executable(
        ${PROJECT_NAME}
        main.cpp
        model/Matrix.h
        model/Matrix.cpp
)

target_link_libraries(lab6 libclew)