//
// Created by mikeasta on 10/16/23.
//
#pragma once
#include <thread>
#include <chrono>
#include "../common/MatrixUtils.h"
#include "../common/ThreadUtils.h"

#define THREADS_AMOUNT 3

int MoreMultipleThreads() {
    // Set random seed
    srand(time(NULL));

    // Initialize matrices
    int leftMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int rightMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Set timer
    auto startTime = std::chrono::high_resolution_clock::now();
    log("Task 1.3 is started.");

    // Matrix generation
    log("First thread started generating matrices");
    std::thread generate(ThreadUtils::generateMatrices, leftMatrix, rightMatrix);
    generate.join();
    log("First thread finished generating matrices");

    // Matrix multiplication
    std::thread threads[THREADS_AMOUNT];
    int matrixItemsAmount = MATRIX_SIZE * MATRIX_SIZE;
    int matrixItemsAmountPerThread = matrixItemsAmount / THREADS_AMOUNT + (matrixItemsAmount % THREADS_AMOUNT != 0);
    log("Defined " + std::to_string(THREADS_AMOUNT) + " threads for multiplying.");

    // Fill mid-threads with tasks
    size_t assignedThreads = 0;
    for (; assignedThreads * matrixItemsAmountPerThread < matrixItemsAmount; assignedThreads++) {
        threads[assignedThreads] = std::thread(
            MatrixUtils::multiplyMatricesUsingThreads,
            leftMatrix,
            rightMatrix,
            resultMatrix,
            assignedThreads * matrixItemsAmountPerThread,
            matrixItemsAmountPerThread
        );
    }

    log("Mid-threads filled with tasks. Multiplying started");
    for (size_t i = 0; i < assignedThreads; i++) threads[i].join();
    log("Mid-threads finished multiplying matrix");

    // Matrix logging
    log("Last thread started logging matrix");
    std::thread logResult(MatrixUtils::logMatrix, resultMatrix);
    logResult.join();
    log("Last thread finished logging matrix");

    log("Task 1.3 is finished.");

    // Stop timer
    auto finishTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
    std::cout << "Performance duration (in microseconds): " << duration.count() << std::endl;

    return 0;
}
