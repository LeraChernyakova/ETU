cmake_minimum_required(VERSION 3.1)

add_subdirectory(libs)

project(main.exe)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp io/input.cpp io/output.cpp utils/utils.cpp matrix/matrix.cpp)
target_link_libraries(${PROJECT_NAME} libclew)
