#ifndef THREAD_H
#define THREAD_H
#include <iostream>
#include "matrix.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <filesystem>
#include <string>
#include <thread>

class Thread
{
public:
    Thread();
    void Create(Matrix& first, Matrix& second,Matrix& result);
    void Multiple(Matrix& first, Matrix& second,Matrix& result,int shiftRow = 0,int threadCount = 1);
    void outPut(Matrix& result);
    void proceedThreads(int choice);
    int N = 100; 
    int M = 100;
    int threadsCount = 32; // количество потоков
};

#endif // THREAD_H
