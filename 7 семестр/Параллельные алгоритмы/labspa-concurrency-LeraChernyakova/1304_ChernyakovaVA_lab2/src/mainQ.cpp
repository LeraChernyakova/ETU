#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

#include "./matrix.h"
#include "./matrix_process.h"
#include "./queue.h"
#include "./values.h"

Queue<std::pair<Matrix, Matrix>> matrixPair;
Queue<Matrix> outputMatrixes;
std::pair<Matrix, Matrix> task;
Matrix resultMatrix;
std::atomic_int producerTasks;
std::atomic_int consumerTasks;
std::mutex fileMutex;

void producer(int mSize) {
	while (producerTasks.load() > 0) {
        producerTasks.fetch_sub(1);
        matrixPair.push({createMatrix(mSize, mSize), createMatrix(mSize, mSize)});
    }
}

void consumer() {
	while (consumerTasks.load() > 0) {
        consumerTasks.fetch_sub(1);
        matrixPair.pop(task);
        resultMatrix = task.first * task.second;
        {
            std::lock_guard<std::mutex> lock(fileMutex);
            printMatrix(resultMatrix, "output_matrix");
        }
    }
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    producerTasks.store(TASKS);
    consumerTasks.store(TASKS);
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

	for (int i = 0; i < PRODUCER; i++) {
    	producers.push_back(std::thread(producer, MATRIX_SIZE));
    }

    for (int i = 0; i < CONSUMER; i++) {
        consumers.push_back(std::thread(consumer));
    }

    for(int i = 0; i < PRODUCER; i++) {
        producers[i].join();
    }

    for(int i = 0; i < CONSUMER; i++) {
        consumers[i].join();
    }

    return 0;
}