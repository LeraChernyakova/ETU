cmake_minimum_required(VERSION 3.14)
project(parllel_algo_lab5)

include(FetchContent)
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(BUILD_SHARED_LIBS OFF)

# For OpenGL we need to install libraries:
# libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
# libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev
#
# For GLEW: libglew-dev
#
# For OpenCL: ocl-icd-opencl-dev and many others, libpocl2 for vm

# add GLEW
add_compile_definitions(GLEW_STATIC)

# add FLTK
set(FLTK_BUILD_FLUID OFF)
set(FLTK_BUILD_TEST OFF)
set(OPTION_USE_SYSTEM_ZLIB OFF)
set(OPTION_USE_SVG OFF)
set(OPTION_USE_WAYLAND OFF)
set(OPTION_PRINT_SUPPORT OFF)
set(OPTION_BUILD_HTML_DOCUMENTATION OFF)
set(OPTION_BUILD_PDF_DOCUMENTATION OFF)
FetchContent_Declare(
    FLTK
    GIT_REPOSITORY https://github.com/fltk/fltk
    GIT_TAG 3600522ae7d2244b69552458e4d82f869a36067b # release-1.3.8
)
FetchContent_MakeAvailable(FLTK)
set(FLTK_INCLUDE_DIRS ${fltk_SOURCE_DIR} ${fltk_BINARY_DIR})
set(FLTK_LINK_DIRS ${fltk_BINARY_DIR}/lib)
set(FLTK_LIBRARIES fltk fltk_gl fltk_images)

set(COMMON_DIR ../common)
set(OPENGL_LIBRARY ${OPENGL_LIBRARY} ${CMAKE_DL_LIBS} GL GLU Xrandr Xext X11 rt)
set(GLEW_LIBRARIES GLEW)

set(ALL_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${FLTK_LIBRARIES} OpenCL::OpenCL)
set(LINK_DIRS ${GLEW_LINK_DIRS} ${FLTK_LINK_DIRS})
set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${FLTK_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${COMMON_DIR})

add_executable (lab5
	"main.cpp"
	"window.cpp"
    "cl_func.cpp"
    "${COMMON_DIR}/utils.cpp"
)

target_include_directories(lab5 PRIVATE ${INCLUDE_DIRS})
target_link_directories(lab5 PRIVATE ${LINK_DIRS})
target_link_libraries(lab5 ${ALL_LIBS})
