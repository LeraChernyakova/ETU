cmake_minimum_required(VERSION 3.10)
project(MatrixOperations)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/object)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/object)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/object)

set(COMMON_SOURCES matrix/matrix.cpp socket/socket.cpp socket/server_socket.cpp)

add_executable(reader process/reader.cpp ${COMMON_SOURCES})
add_executable(writer process/writer.cpp ${COMMON_SOURCES})
add_executable(main process/main.cpp ${COMMON_SOURCES})
add_executable(3_thread thread/3_thread.cpp ${COMMON_SOURCES})
add_executable(p_thread thread/p_thread.cpp ${COMMON_SOURCES})

target_link_libraries(3_thread pthread)
target_link_libraries(p_thread pthread)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "reader;writer;main;3_thread;p_thread")
