#ifndef PROCESSES_DEFINITIONS_H
#define PROCESSES_DEFINITIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ErrorWriter.h"

#define SHMID 2001
#define PERMS 0666

#define MAX_MATRIX_SIZE 16

template <typename T>
struct Matrix {
    T data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    int height = 0;
    int width = 0;
};

enum process 
{
    READ,
    CALCULATE,
    WRITE
};
enum matrix {A, B, C};
enum status 
{
    START,
    READY,
    RUN,
    TERMINATE
};

#endif
