cmake_minimum_required(VERSION 3.1)

add_subdirectory(libs)

project(enumDevices)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DKERNEL_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/mandelbrot.cl")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} libclew)
