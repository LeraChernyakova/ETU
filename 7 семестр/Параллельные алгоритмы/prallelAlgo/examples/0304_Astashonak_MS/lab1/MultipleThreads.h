//
// Created by mikeasta on 10/16/23.
//
#pragma once
#include <thread>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "../common/MatrixUtils.h"
#include "../common/ThreadUtils.h"

int MultipleThreads() {
    // Set random seed
    srand(time(NULL));

    // Initialize matrices
    int leftMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int rightMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Set timer
    auto startTime = std::chrono::high_resolution_clock::now();
    log("Task 1.2 is started.");

    // Matrix generation
    log("First thread started generating matrices");
    std::thread generate(ThreadUtils::generateMatrices, leftMatrix, rightMatrix);
    generate.join();
    log("First thread finished generating matrices");

    // Matrix multiplication
    log("Second thread started multiplying matrices");
    std::thread multiply(MatrixUtils::multiplyMatrices, leftMatrix, rightMatrix, resultMatrix);
    multiply.join();
    log("Second thread finished multiplying matrices");

    // Matrix logging
    log("Third thread started logging matrix");
    std::thread logResult(MatrixUtils::logMatrix, resultMatrix);
    logResult.join();
    log("Third thread finished logging matrix");

    log("Task 1.2 is finished.");

    // Stop timer
    auto finishTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
    std::cout << "Performance duration (in microseconds): " << duration.count() << std::endl;

    return 0;
}