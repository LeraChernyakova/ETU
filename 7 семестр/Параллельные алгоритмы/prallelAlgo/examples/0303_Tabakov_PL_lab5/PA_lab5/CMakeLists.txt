cmake_minimum_required(VERSION 3.1)

add_subdirectory(libs)

project(mandelbrot)

set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cl/mandelbrot.cl
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(
     ${PROJECT_NAME} 
     main.cpp 
)
target_link_libraries(${PROJECT_NAME} libclew)
