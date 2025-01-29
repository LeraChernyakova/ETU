#include "./common_funcs.h"
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <functional>
#include<unistd.h>
#include<utility>
#include<future>
#include<vector>

using namespace std;

void runProcess(const function<void(int*)> &func, int*);

int writeToPointerFromFile(ifstream& in, int* ptr, int ptrOffset);

void matrixPrepare(int*);

int multiplyRowCol(int* ptr, PAIR_INT& dim1, PAIR_INT& dim2, PAIR_INT& cur);

void matrixCalculate(int*);

void matrixPrintToFile(int*);

void matrixPrint(int*);

void clearSharedMem();

void* createSharedMem();