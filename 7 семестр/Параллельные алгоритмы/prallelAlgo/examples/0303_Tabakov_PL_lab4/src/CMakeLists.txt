cmake_minimum_required(VERSION 3.15.0)

cmake_policy(SET CMP0016 NEW)

project(Test)

include_directories(${CMAKE_SOURCE_DIR})

SET(HEADERS "matrtix.h")

SET(SRC_FILES "matrix.cpp" "main.cpp")

add_executable(main ${SRC_FILES})

