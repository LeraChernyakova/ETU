cmake_minimum_required(VERSION 3.1)

add_subdirectory(libs)

project(lab6)

set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/m_mult.cl
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR})

add_executable(
     ${PROJECT_NAME} 
     main.cpp 
     matrix.cpp
)

target_link_libraries(${PROJECT_NAME} libclew)
