cmake_minimum_required(VERSION 2.8)
project(lb4)

SET(GCC_COVERAGE_COMPILE_FLAGS "-O3 ")
SET(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})

file(GLOB_RECURSE FILES
    src/*.cpp
    src/*.hpp
)

add_executable(${PROJECT_NAME}
    ${FILES}
)