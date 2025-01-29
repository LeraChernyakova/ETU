#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <atomic>
#include "./matrix.h"
#include "./common.h"
#include "./queue.h"

Queue<std::pair<Matrix, Matrix>> matrixPair;
Queue<Matrix> outputMatrixes;
std::atomic_int pCountCurrent{0};
std::atomic_int cCountCurrent{0};


void producer(int taskCount, int mSize) {
    for (int i = 0; i < taskCount; i++) {
        matrixPair.push({createMatrix(mSize, mSize), createMatrix(mSize, mSize)});
    }
    --pCountCurrent;
    if (pCountCurrent == 0) {
        matrixPair.setEnd();
    }
}

void consumer() {
    std::pair<Matrix, Matrix> task;
    while (matrixPair.pop(task)) {
        outputMatrixes.push(task.first * task.second);
    }
    --cCountCurrent;
    if (cCountCurrent == 0) {
        outputMatrixes.setEnd();
    }
}

void showResults() {
    Matrix resultMatrix;
    while (outputMatrixes.pop(resultMatrix)) {
        printMatrix(resultMatrix);
    } 
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    int cCount, pCount, taskCount, matrixSize;
    if (argc != 5 || !readInt(argv[1], cCount) || !readInt(argv[2], pCount)
        || !readInt(argv[3], taskCount)|| !readInt(argv[4], matrixSize))
    {
        std::cout << "Usage: " << argv[0] << " cCount pCount taskCount matrixSize\n";
        return 1;
    }
    pCountCurrent = pCount;
    cCountCurrent = cCount;
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < pCount; i++) {
        producers.push_back(std::thread(producer, taskCount, matrixSize));
    }

    for (int i = 0; i < cCount; i++) {
        consumers.push_back(std::thread(consumer));
    }

    std::thread output(showResults);

    for(int i = 0; i < pCount; i++) {
        producers[i].join();
    }

    for(int i = 0; i < cCount; i++) {
        consumers[i].join();
    }
    output.join();

    return 0;
}