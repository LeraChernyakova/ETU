#pragma once

#include <iostream>
#include <thread>
#include "Utils.h"

using namespace std;

namespace ForSingleThread {
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

int mainSingleThread() {
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
    thread input(ForSingleThread::readMatricesFromFiles, firstMatrix, secondMatrix);
    input.join();
    log("step 1: данные получены из файлов");

    // step 2: считаем произведение
    log("step 2: начался");
    thread multiply(MatrixUtils::multiplyMatrices, firstMatrix, secondMatrix, resultMatrix);
    multiply.join();
    log("step 2: произведение посчитано");

    // step 3: записываем результат в файл
    log("step 3: начался");
    thread output(ForSingleThread::writeMatrixToFile, resultMatrix);
    output.join();
    log("step 3: результат записан в файл");

    auto finishTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
    cout << duration.count();

    return 0;
}
