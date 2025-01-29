#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <functional>
#include "../model/Matrix.h"
#include "../model/MultiplicationMatrix.h"
//#define fromFile

void startProcccess(const std::function<void()> &fun){
    auto pid = fork();
    switch(pid){
        case 0:
            fun();
            exit(0);
        case -1:
            std::cout << "fork bomb!\n";
            break;
        default:
            wait(&pid); 
    }
}

void *getSharedPtr(){
    const int size = 1024;

    auto id = shmget(1, size, 0644 | IPC_CREAT);
    if (id == -1) {
        throw std::runtime_error("Error");
    }
    auto pointer = shmat(id, nullptr, 0);
    if (pointer == (void *) -1) {
        throw std::runtime_error("Error");
    }
    return pointer;
}

void readMatrix(){
#ifndef fromFile
    Matrix left = Matrix::generate();
    Matrix right = Matrix::generate();
#endif
#ifdef fromFile
    std::ifstream file("../input.txt");
    Matrix left, right;
    file >> left >> right;
    file.close();
#endif
    auto sharedPtr = (int *) getSharedPtr();
    auto ptr = left.writeToPtr(sharedPtr);
    right.writeToPtr(ptr);
}

void multiply(){
    auto sharedPtr = (int *) getSharedPtr();
    auto leftMatrixWithPtr = Matrix::readFromPtr(sharedPtr);
    auto leftMatrix = leftMatrixWithPtr.first;
    auto rightMatrix = Matrix::readFromPtr(leftMatrixWithPtr.second).first;
    MultiplicationMatrix mul = MultiplicationMatrix::create(leftMatrix, rightMatrix);
    Matrix result = mul.multiply();
    result.writeToPtr(sharedPtr);
}

void writematrix(){
    auto sharedPtr = (int *) getSharedPtr();
    auto matrix = Matrix::readFromPtr(sharedPtr).first;
    std::ofstream file("../result.txt");
    file << matrix;
    file.close();
}

int main(){
    startProcccess(readMatrix);
    startProcccess(multiply);
    startProcccess(writematrix);
    return 0;
}