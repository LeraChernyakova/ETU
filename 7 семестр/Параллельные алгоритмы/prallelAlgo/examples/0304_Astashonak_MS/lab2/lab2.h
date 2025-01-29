//
// Created by mikeasta on 11/2/23.
//
#pragma once

#include <thread>
#include <vector>
#include <chrono>
#include "HardBlockingQueue.h"
#include "FineBlockingQueue.h"
#include "../common/MatrixUtils.h"

#define MAX_PRODUCERS_AMOUNT 20
#define MAX_CONSUMERS_AMOUNT 20
#define EXPERIMENTS_AMOUNT 10

using Cell = std::pair<int, int>;
using Matrix = int[MATRIX_SIZE][MATRIX_SIZE];
//using Queue = HardBlockingQueue<Cell>;
using Queue = FineBlockingQueue<Cell>;

void createProducerTask(Queue &queue, int startPosition, int itemsAmountPerThread) {
        int currentItemIndex = startPosition;
        int matrixItemsAmount = MATRIX_SIZE * MATRIX_SIZE;

        while (currentItemIndex < matrixItemsAmount && (currentItemIndex - startPosition) < itemsAmountPerThread) {
            int i = currentItemIndex / MATRIX_SIZE;
            int j = currentItemIndex % MATRIX_SIZE;
            queue.push(Cell(i, j));
            currentItemIndex++;
        }
}

void createConsumerTask(
        Queue &queue,
        Matrix &leftMatrix,
        Matrix &rightMatrix,
        Matrix &resultMatrix,
        int itemsAmountPerThread) {

    while (itemsAmountPerThread--) {
        std::shared_ptr<Cell> cellPointer = queue.popWithWaiting();
        if (!cellPointer) break;

        Cell cell = *(cellPointer);
        MatrixUtils::multiplyMatricesCell(
                cell.first,
                cell.second,
                leftMatrix,
                rightMatrix,
                resultMatrix);
    }
}

void scheduleProducersAndConsumers(
        int producerAmount,
        int consumerAmount,
        Matrix& leftMatrix,
        Matrix& rightMatrix,
        Matrix& resultMatrix) {
    log("Producer-Consumer scheduling started.");
    Queue queue;
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    producers.reserve(producerAmount);
    consumers.reserve(consumerAmount);
    int matrixItemsAmount = MATRIX_SIZE * MATRIX_SIZE;

    // 1. Fill producers tasks
    int itemsAmountPerProducer = matrixItemsAmount / producerAmount + (matrixItemsAmount % producerAmount != 0);
    for (size_t i = 0; i < producerAmount; i++) {
        producers.emplace_back(
                createProducerTask,
                std::ref(queue),
                i * itemsAmountPerProducer,
                i == producerAmount - 1 ? matrixItemsAmount - (producerAmount - 1) * itemsAmountPerProducer:
                itemsAmountPerProducer);
    }
    log("Producers tasks defined.");

    // 2. Fill Consumers tasks
    int itemsAmountPerConsumer = matrixItemsAmount / consumerAmount + (matrixItemsAmount % consumerAmount != 0);
    for (size_t i = 0; i < consumerAmount; i++) {
        consumers.emplace_back(
                createConsumerTask,
                std::ref(queue),
                std::ref(leftMatrix),
                std::ref(rightMatrix),
                std::ref(resultMatrix),
                i == consumerAmount - 1 ? matrixItemsAmount - (consumerAmount - 1) * itemsAmountPerConsumer:
                itemsAmountPerConsumer);
    }
    log("Consumers tasks defined.");


    // 3. Start threads
    for (auto &&thread: producers) thread.join();
    log("Producers threads started.");

    for (auto &&thread: consumers) thread.join();
    log("Consumers threads started.");

    MatrixUtils::logMatrix(resultMatrix);
}

void performExperiment(int producerAmount, int consumerAmount, int experimentsAmount) {
    log("Experiments started.");

    std::vector<long long> durations(experimentsAmount);

    for (size_t experimentIndex = 0; experimentIndex < experimentsAmount; experimentIndex++) {
        Matrix leftMatrix;
        Matrix rightMatrix;
        Matrix resultMatrix;

        MatrixUtils::generateMatrix(leftMatrix);
        MatrixUtils::generateMatrix(rightMatrix);

        auto startTime = std::chrono::high_resolution_clock::now();
        scheduleProducersAndConsumers(producerAmount, consumerAmount, leftMatrix, rightMatrix, resultMatrix);
        auto finishTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
        durations[experimentIndex] = duration.count();
    }

    long long duration_sum = 0;
    for (size_t i = 0; i < experimentsAmount; i++) {
        duration_sum += durations[i];
        log("Experiment #" + std::to_string(i+1) + ": duration - " + std::to_string(durations[i]) + ".");
    }

    log("Mean duration: " + std::to_string(duration_sum / durations.size()) + ".");
}

int lab2() {
    performExperiment(MAX_PRODUCERS_AMOUNT, MAX_CONSUMERS_AMOUNT, EXPERIMENTS_AMOUNT);
    return 0;
}

