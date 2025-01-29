cmake_minimum_required(VERSION 3.26)
project(PA_Lab_2)

set(CMAKE_CXX_STANDARD 23)

add_executable(PA_Lab_2 main.cpp
        model/queue/impl/Thread_safe_queue_impl.h
        model/queue/impl/Thread_safe_queue_impl_fine.h
        model/queue/Thread_safe_queue.h
        model/Square_matrix.cpp
        model/Square_matrix.h
        thread/Matrix_threading.cpp
        thread/Matrix_threading.h)
