cmake_minimum_required(VERSION 3.19)
project(AMoh)

set(CMAKE_CXX_STANDARD 17)

add_executable(AMoh main.cpp FF.cpp kmp_cycle.cpp aho.cpp)