#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <atomic>
#include "./matrix.h"
#include "./common.h"
#include "./lockFreeQueue.h"

std::atomic_int tasksToComplete{0};
std::atomic_int outputMatrixLeft{0};



void producer(LockFreeQueue<std::pair<Matrix, Matrix>>& matrixPair, int threadNum, int taskCount, int mSize) {
    for (int i = 0; i < taskCount; i++) {
        matrixPair.push({createMatrix(mSize, mSize), createMatrix(mSize, mSize)}, threadNum);
    }
}

void consumer(LockFreeQueue<std::pair<Matrix, Matrix>>& matrixPair,
     LockFreeQueue<Matrix>& outputMatrixes, int threadNumMP, int threadNumO) {
    std::pair<Matrix, Matrix> task;
    while (tasksToComplete > 0) {
        if (matrixPair.pop(task, threadNumMP)) {
            tasksToComplete--;
            outputMatrixes.push(task.first * task.second, threadNumO);
        }
    }
}

void showResults(LockFreeQueue<Matrix>& outputMatrixes, int threadNum) {
    Matrix resultMatrix;
    while (outputMatrixLeft > 0) {
        if (outputMatrixes.pop(resultMatrix, threadNum)) {
            outputMatrixLeft--;
            printMatrix(resultMatrix);
        }
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
    LockFreeQueue<std::pair<Matrix, Matrix>> matrixPair(pCount + cCount);
    LockFreeQueue<Matrix> outputMatrixes(cCount + 1);

    tasksToComplete = taskCount * pCount;
    outputMatrixLeft = taskCount * pCount;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    int i, j;

    for (i = 0; i < pCount; i++) {
        producers.push_back(std::thread(producer, std::ref(matrixPair), i, taskCount, matrixSize));
    }

    for (j = 0; j < cCount; j++, i++) {
        consumers.push_back(std::thread(consumer, std::ref(matrixPair), std::ref(outputMatrixes), i, j));
    }

    std::thread output(showResults, std::ref(outputMatrixes), j);

    for(int i = 0; i < pCount; i++) {
        producers[i].join();
    }

    for(int i = 0; i < cCount; i++) {
        consumers[i].join();
    }
    output.join();

    return 0;
}