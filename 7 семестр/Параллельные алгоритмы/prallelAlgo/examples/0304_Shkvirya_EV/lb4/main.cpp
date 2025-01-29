//#define DEBUG

#include <iostream>
#include <chrono>
#include <vector>
#include "Utils.hpp"
#include "DefaultMultiplication.hpp"
#include "Strassen.hpp"
#include "Matrix.hpp"

#define MATRIX_SIZE 2048
#define EXPERIMENTS_AMOUNT 2

using namespace std;

using Multiplier = Strassen;

long makeExperiment() {
    log("experiment started with " + to_string(MATRIX_SIZE) + " matrix size, experimentsAmount " + to_string(EXPERIMENTS_AMOUNT));
    vector<long long> durations(EXPERIMENTS_AMOUNT);

    for (int i = 0; i < EXPERIMENTS_AMOUNT; i++) {

        Matrix firstMatrix(MATRIX_SIZE, MATRIX_SIZE);
        Matrix secondMatrix(MATRIX_SIZE, MATRIX_SIZE);
        Matrix resultMatrix(MATRIX_SIZE, MATRIX_SIZE);

        firstMatrix.fillMatrix();
        secondMatrix.fillMatrix();
        auto startTime = chrono::high_resolution_clock::now();
        Multiplier::defaultMatrixMultiplication(firstMatrix, secondMatrix, resultMatrix);
        auto finishTime = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
        durations[i] = duration.count();
    }
    long long durationsSum = 0;
    for (int i = 0; i < durations.size(); i++) {
        durationsSum += durations[i];
    }

    return ((long long) durationsSum) / EXPERIMENTS_AMOUNT;
}

int main() {
    cout << makeExperiment() << '\n';
}