#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include "Utils.h"

using namespace std;

namespace ForMultiThread {
    void readMatricesFromFiles(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
        MatrixUtils::readFromFile(firstMatrix, FIRST_MATRIX_FILE);
        log("step 1: первая матрица получена");
        MatrixUtils::readFromFile(secondMatrix, SECOND_MATRIX_FILE);
        log("step 1: вторая матрица получена");
    }

    void writeMatrixToFile(int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
        MatrixUtils::writeToFile(resultMatrix, RESULT_MATRIX_FILE);
    }
}

#define COUNT_THREADS 14

void mainMultiThread() {
    srand(time(nullptr));

    // step 0: инициализация

    int firstMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int secondMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];
    MatrixUtils::fillMatrix(firstMatrix);
    MatrixUtils::fillMatrix(secondMatrix);
    MatrixUtils::writeToFile(firstMatrix, FIRST_MATRIX_FILE);
    MatrixUtils::writeToFile(secondMatrix, SECOND_MATRIX_FILE);

    auto startTime = std::chrono::high_resolution_clock::now();

    // step 1: ввод данных
    log("step 1: начался");
    thread input(ForMultiThread::readMatricesFromFiles, firstMatrix, secondMatrix);
    input.join();
    log("step 1: данные получены из файлов");

    // step 2: считаем произведение
    log("step 2: начался");
    thread threads[COUNT_THREADS];
    int assignedThreadsCount = 0;
    int matrixItemsAmount = MATRIX_SIZE * MATRIX_SIZE;
    int itemsAmountPerThread = matrixItemsAmount / COUNT_THREADS + (matrixItemsAmount % COUNT_THREADS != 0);

    // step 2: заполняем пул потоков
    threads[assignedThreadsCount] = thread(MatrixUtils::multiplyMatricesInThread,firstMatrix, secondMatrix, resultMatrix, 0, itemsAmountPerThread);
    assignedThreadsCount++;
    while (assignedThreadsCount * itemsAmountPerThread < matrixItemsAmount) {
        threads[assignedThreadsCount] = thread(MatrixUtils::multiplyMatricesInThread,firstMatrix, secondMatrix, resultMatrix, assignedThreadsCount * itemsAmountPerThread, itemsAmountPerThread);
        assignedThreadsCount++;
    }
    log("step 2: подготовка закончена");
    for (int i = 0; i < assignedThreadsCount; ++i) {
        threads[i].join();
    }
    log("step 2: произведение посчитано");

    // step 3: записываем результат в файл
    log("step 3: начался");
    thread output(ForMultiThread::writeMatrixToFile, resultMatrix);
    output.join();
    log("step 3: результат записан в файл");

    auto finishTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
    cout << duration.count() << '\n';
}
