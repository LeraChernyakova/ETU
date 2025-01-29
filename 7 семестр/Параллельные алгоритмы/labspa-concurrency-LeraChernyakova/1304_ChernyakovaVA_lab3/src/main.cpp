#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <atomic>
#include "./matrix.h"
#include "./matrix_process.h"
#include "./lockFreeQueue.h"
#include "./values.h"

std::atomic_int pTasks;
std::atomic_int cTasks;

void producer(LockFreeQueue<std::pair<Matrix, Matrix>>& matrixPair, int threadNum, int mSize) {
    while (pTasks.load() > 0) {
        pTasks.fetch_sub(1);
        matrixPair.push({createMatrix(mSize, mSize), createMatrix(mSize, mSize)}, threadNum);
    }
}

void consumer(LockFreeQueue<std::pair<Matrix, Matrix>>& matrixPair, int cNumber) {
    while (cTasks.load() > 0) {
        std::pair<Matrix, Matrix> task;
        if (matrixPair.pop(task, cNumber)) {
            cTasks.fetch_sub(1);
            printMatrix(task.first * task.second, "result");
        }
    }
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    int taskCount, matrixSize;

    pTasks.store(TASKS);
    cTasks.store(TASKS);

    int pCount = PRODUCER;
    int cCount = CONSUMER;
    matrixSize = MATRIX_SIZE;

    LockFreeQueue<std::pair<Matrix, Matrix>> matrixPair(pCount + cCount);

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < pCount; i++) {
        producers.push_back(std::thread(producer, std::ref(matrixPair), i, matrixSize));
    }

    for (int j = 0; j < cCount; j++) {
        consumers.push_back(std::thread(consumer, std::ref(matrixPair), j));
    }

    for(int i = 0; i < pCount; i++) {
        producers[i].join();
    }

    for(int i = 0; i < cCount; i++) {
        consumers[i].join();
    }

    return 0;
}