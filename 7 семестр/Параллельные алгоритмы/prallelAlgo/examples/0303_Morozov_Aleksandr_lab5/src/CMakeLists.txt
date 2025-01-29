cmake_minimum_required(VERSION 3.1)

add_subdirectory(libs)

project(ex_mandelbrot)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/utils)

set(CMAKE_CXX_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/cl/kernel.cl
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(
     ${PROJECT_NAME} 
     src/main.cpp 
     utils/create_device.cpp
     utils/build_program.cpp
     utils/invoke_kernel.cpp
     utils/save_result.cpp
)
target_link_libraries(${PROJECT_NAME} libclew)
