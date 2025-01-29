cmake_minimum_required(VERSION 3.22.1)
project(processes)

set(CMAKE_CXX_STANDARD 17)

add_executable(processes main.cpp
	Process.h
	ErrorWriter.cpp ErrorWriter.h
        SharedMemory.cpp SharedMemory.h
        ReadProcess.cpp ReadProcess.h
        CalculateProcess.cpp CalculateProcess.h
        WriteProcess.cpp WriteProcess.h
        definitions.h)
