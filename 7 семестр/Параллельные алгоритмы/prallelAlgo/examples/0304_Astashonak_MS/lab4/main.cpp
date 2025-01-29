#include <iostream>
#include <chrono>
#include <vector>
#include "Utils.h"
#include "Matrix.h"
#include "DefaultMultiplier.h"
#include "StrassenMultiplier.h"

#define MATRIX_SIZE 8
#define EXPERIMENTS_AMOUNT 10
#define STRASSEN_APPROACH true

long performExperiment() {
    log("Multiplication experiment started!");
    std::vector<long long> durations(EXPERIMENTS_AMOUNT);

    for (size_t i = 0; i < EXPERIMENTS_AMOUNT; i++) {
        // Initialize matrices
        Matrix leftMatrix(MATRIX_SIZE, MATRIX_SIZE);
        Matrix rightMatrix(MATRIX_SIZE, MATRIX_SIZE);
        Matrix resultMatrix(MATRIX_SIZE, MATRIX_SIZE);

        leftMatrix.fill();
        rightMatrix.fill();

        auto startTime = std::chrono::high_resolution_clock::now();
        STRASSEN_APPROACH ?
            StrassenMultiplier::defaultMatrixMultiplication(leftMatrix, rightMatrix, resultMatrix):
            DefaultMultiplier::defaultMatrixMultiplication(leftMatrix, rightMatrix, resultMatrix);
        auto finishTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
        durations[i] = duration.count();
    }

    long long durationsSum = 0;
    for (size_t i = 0; i < EXPERIMENTS_AMOUNT; i++)
        durationsSum += durations[i];

    return ((long long) durationsSum) / EXPERIMENTS_AMOUNT;
}

int main() {
    std::cout << performExperiment() << std::endl;
    return 0;
}
