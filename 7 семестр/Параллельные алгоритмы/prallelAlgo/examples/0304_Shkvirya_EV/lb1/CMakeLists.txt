cmake_minimum_required(VERSION 3.16.3)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp MainProcess.h
        MainSingleThread.h
        Utils.h
        MainMultiThreads.h)
