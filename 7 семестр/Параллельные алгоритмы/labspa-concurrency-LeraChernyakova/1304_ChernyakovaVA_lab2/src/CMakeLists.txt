cmake_minimum_required(VERSION 3.10)
project(MatrixOperations)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/object)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/object)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/object)

set(COMMON_SOURCES
        matrix.cpp
        matrix_process.cpp
)

add_executable(mainL
        mainL.cpp
        ${COMMON_SOURCES}
)

add_executable(mainQ
        mainQ.cpp
        ${COMMON_SOURCES}
)

target_link_libraries(mainL pthread)
target_link_libraries(mainQ pthread)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "mainL;mainQ")
