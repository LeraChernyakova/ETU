cmake_minimum_required(VERSION 3.14)
project(parllel_algo_lab6)

include(FetchContent)
find_package(OpenCL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(BUILD_SHARED_LIBS OFF)

set(COMMON_DIR ../common)

add_executable (lab6
	"main.cpp"
    "cl_matr.cpp"
    "${COMMON_DIR}/utils.cpp"
    "${COMMON_DIR}/matrix.cpp"
    "${COMMON_DIR}/matrix_slice.cpp"
)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -pthread)
target_include_directories(lab6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${COMMON_DIR})
target_link_directories(lab6 PRIVATE ${LINK_DIRS})
target_link_libraries(lab6 OpenCL::OpenCL)
