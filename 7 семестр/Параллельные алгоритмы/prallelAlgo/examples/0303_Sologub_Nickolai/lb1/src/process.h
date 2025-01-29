#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include "matrix.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <filesystem>
#include <string>
#include <chrono>

class Process
{
public:
    Process();
    void consoleOutput(int* buf);
    int  ProceedProcess();
};

#endif // PROCESS_H
