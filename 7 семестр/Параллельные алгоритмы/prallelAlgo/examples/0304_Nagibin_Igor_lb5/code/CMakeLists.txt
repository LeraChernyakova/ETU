cmake_minimum_required(VERSION 3.22)
project(lb5)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCL REQUIRED)

add_subdirectory(libs)

file(GLOB_RECURSE PROJECT_FILES
    src/*.cpp
    src/*.hpp
    src/*.c
    src/*.h
    )
    
add_executable(${PROJECT_NAME} ${PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} libclew)
# target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)
