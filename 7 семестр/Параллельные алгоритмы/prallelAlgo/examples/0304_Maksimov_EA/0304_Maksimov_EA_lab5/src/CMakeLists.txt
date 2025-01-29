cmake_minimum_required(VERSION 3.1)

add_subdirectory(libs)

project(main.exe)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp io/input.cpp io/output.cpp mandelbrot/mandelbrot.cpp utils/utils.cpp)
target_link_libraries(${PROJECT_NAME} libclew)
