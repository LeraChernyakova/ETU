#pragma once

#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <iostream>
#include <chrono>
#include <sys/user.h>
#include "Utils.h"

using namespace std;

void mainProcess() {
    srand(time(nullptr));

    pid_t pid1, pid2;
    int status1, status2;

    // step 0: инициализация

    int firstMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int secondMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];
    MatrixUtils::fillMatrix(firstMatrix);
    MatrixUtils::fillMatrix(secondMatrix);
    MatrixUtils::writeToFile(firstMatrix, FIRST_MATRIX_FILE);
    MatrixUtils::writeToFile(secondMatrix, SECOND_MATRIX_FILE);

    key_t key = 10;
    int sharedMemoryId = shmget(key, MATRIX_SIZE * MATRIX_SIZE * 2, 0666 | IPC_CREAT);

    int *sharedMatrices = (int*) shmat(sharedMemoryId, nullptr, 0); // nullptr - система выберет участок памяти сама

    auto startTime = std::chrono::high_resolution_clock::now();
    pid1 = fork();

    if (pid1 == 0) {
        // процесс-потомок
        // step 1: ввод данных

        log("step 1: начался");

        MatrixUtils::readFromFile(firstMatrix, FIRST_MATRIX_FILE);
        MatrixUtils::readFromFile(secondMatrix, SECOND_MATRIX_FILE);

        log("step 1: данные получены из файлов");

        // сохраняем данные в sharedMemory для других процессов
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                sharedMatrices[i * MATRIX_SIZE + j] = firstMatrix[i][j];
            }
        }
        int offset = MATRIX_SIZE * MATRIX_SIZE;
        log("step 1: первая матрица сохранена, offset для следующей = " + to_string(offset));
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                sharedMatrices[offset + i * MATRIX_SIZE + j] = secondMatrix[i][j];
            }
        }
        log("step 1: вторая матрица сохранена");
        log("step 1: данные сохранены в sharedMemory");
        exit(0);
    } else {
        // процесс-родитель
        waitpid(pid1, &status1, 0);

        pid2 = fork();

        if (pid2 == 0) {
            // процесс-потомок
            // step 2: считаем произведение
            log("step 2: начался");

            // получаем данные из sharedMemory от step 2
            for (int i = 0; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    firstMatrix[i][j] = sharedMatrices[i * MATRIX_SIZE + j];
                }
            }
            int offset = MATRIX_SIZE * MATRIX_SIZE;
            for (int i = 0; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    secondMatrix[i][j] = sharedMatrices[offset + i * MATRIX_SIZE + j];
                }
            }
            log("step 2: данные получены из sharedMemory");

            MatrixUtils::multiplyMatrices(firstMatrix, secondMatrix, resultMatrix);

            log("step 2: произведение посчитано");

            // кладём результат в sharedMemory
            for (int i = 0; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    sharedMatrices[i * MATRIX_SIZE + j] = resultMatrix[i][j];
                }
            }
            log("step 2: результат сохранён в sharedMemory");

            exit(0);
        } else {
            // процесс-родитель
            waitpid(pid2, &status2, 0);

            // step 3: записываем результат в файл
            log("step 3: начался");

            for (int i = 0; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    resultMatrix[i][j] = sharedMatrices[i * MATRIX_SIZE + j];
                }
            }
            log("step 3: результат получен из sharedMemory");

            MatrixUtils::writeToFile(resultMatrix, RESULT_MATRIX_FILE);
            log("step 3: результат записан в файл");

            auto finishTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
            cout << duration.count();

            shmdt(sharedMatrices);
            shmctl(sharedMemoryId, IPC_RMID, nullptr);
        }
    }
}