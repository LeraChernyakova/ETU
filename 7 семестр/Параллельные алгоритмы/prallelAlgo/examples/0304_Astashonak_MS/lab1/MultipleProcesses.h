//
// Created by mikeasta on 10/16/23.
//
#pragma once
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "../common/SharedMemoryUtils.h"

int MultipleProcesses() {
    // Set random seed
    srand(time(NULL));

    // Initialize variables
    pid_t pid1, pid2;
    int status1, status2;
    int leftMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int rightMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Initialize shared memory segment
    key_t sharedMemoryKey = 10;
    int sharedMemoryAddress = shmget(
            sharedMemoryKey,
            MATRIX_SIZE * MATRIX_SIZE * 2,
            0666 | IPC_CREAT);
    int* sharedMemoryMatrices = (int*) shmat(
            sharedMemoryAddress,
            NULL,
            0);

    // Set timer
    auto startTime = std::chrono::high_resolution_clock::now();
    log("Task 1.1 is started.");

    // Fork processes
    pid1 = fork();

    if (pid1 == 0) {
        log("Process 1 (child) - Generating.");

        // Generating
        MatrixUtils::generateMatrix(leftMatrix);
        MatrixUtils::generateMatrix(rightMatrix);

        // Saving to shared memory
        SharedMemoryUtils::saveTwoMatrices(leftMatrix, rightMatrix, sharedMemoryMatrices);
        log("Process 1 finished: matrices are generated and saved to shared memory.");
        exit(0);
    } else {
        waitpid(pid1, &status1, 0);
        pid2 = fork();

        if (pid2 == 0) {
            log("Process 2 (child) - Multiplication.");

            // Getting data from shared memory
            SharedMemoryUtils::getTwoMatrices(leftMatrix, rightMatrix, sharedMemoryMatrices);

            // Multiplication
            MatrixUtils::multiplyMatrices(leftMatrix, rightMatrix, resultMatrix);

            // Saving result matrix
            SharedMemoryUtils::saveMatrix(resultMatrix, sharedMemoryMatrices);
            log("Process 2 finished: matrices are multiplied - result is saved to shared memory.");
            exit(0);
        } else {
            waitpid(pid2, &status2, 0);
            log("Process 3 (parent) - Logging.");

            // Getting result matrix
            SharedMemoryUtils::getMatrix(resultMatrix, sharedMemoryMatrices);

            // Log result matrix
            log("Result matrix:");
            MatrixUtils::logMatrix(resultMatrix);

            log("Process 3 finished: result is logged.");
            log("Task 1.1 is finished.");

            // Stop timer
            auto finishTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
            std::cout << "Performance duration (in microseconds): " << duration.count() << std::endl;

            // Clear shared memory
            shmdt(sharedMemoryMatrices);
            shmctl(sharedMemoryAddress, IPC_RMID, NULL);
        }
    }
    return 0;
}