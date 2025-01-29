cmake_minimum_required(VERSION 3.14)
project(ComputerGraphics)

find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
    cmake_policy(SET CMP0077 NEW)
endif()

set(BUILD_SHARED_LIBS OFF)

add_compile_definitions(GLEW_STATIC)

set(OPENGL_LIBRARY ${OPENGL_LIBRARY} ${CMAKE_DL_LIBS} GL GLU Xrandr Xext X11 rt)
set(GLEW_LIBRARIES GLEW)
set(GLFW_LIBRARIES glfw)

set(ALL_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} OpenCL::OpenCL)
set(LINK_DIRS ${GLEW_LINK_DIRS} ${GLFW_LINK_DIRS})
set(INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (lab5
	"main.cpp"
    "mandelbrot.cpp"
)

target_include_directories(lab5 PRIVATE ${INCLUDE_DIRS})
target_link_directories(lab5 PRIVATE ${LINK_DIRS})
target_link_libraries(lab5 ${ALL_LIBS})
