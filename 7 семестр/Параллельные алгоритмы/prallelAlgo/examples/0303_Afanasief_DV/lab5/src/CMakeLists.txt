cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)

project(lab5)

add_executable(
        ${PROJECT_NAME}
        main.cpp
        mandelbrot.h
        mandelbrot.cpp
)

target_link_libraries(lab5 libclew)