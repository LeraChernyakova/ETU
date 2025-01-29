// #define DEBUG

#include <iostream>
#include <thread>
#include <chrono>
#include "Utils.hpp"
#include "ThreadSafeHardQueue.hpp"
#include "ThreadSafeFineQueue.hpp"

#define MATRIX_SIZE 300
#define MAX_PRODUCERS_SIZE 15
#define MAX_CONSUMERS_SIZE 15
#define EXPERIMENTS_AMOUNT 10

using namespace std;

using Point = pair<int, int>;
using Matrix = vector<vector<int>>;
// using ThreadSafeQueue = ThreadSafeHardQueue<Point>;
using ThreadSafeQueue = ThreadSafeFineQueue<Point>;

void createProducerTask(ThreadSafeQueue &queue,
                        int numberOfProducer,
                        int startPosition,
                        int amountItemsPerThread,
                        int matrixSize) {
    int currentItem = startPosition;
    int matrixItemsAmount = matrixSize * matrixSize;

    while (currentItem < matrixItemsAmount && currentItem - startPosition < amountItemsPerThread) {
        int i = currentItem / matrixSize;
        int j = currentItem % matrixSize;
        queue.push(Point(i, j));
        currentItem++;
    }
#ifdef DEBUG
    log("producer #" + to_string(numberOfProducer) + " has finished");
#endif
}

void createConsumerTask(ThreadSafeQueue &queue,
                        int numberOfConsumer,
                        const Matrix &firstMatrix,
                        const Matrix &secondMatrix,
                        Matrix &resultMatrix,
                        int amountItemsPerThread) {
    while (amountItemsPerThread--) {
        shared_ptr<Point> pointPtr = queue.popWithWaiting();
        if (pointPtr == nullptr) {
            break;
        }
        Point point = *(pointPtr);
        MatrixUtils::multiplyMatricesItem(point.first, point.second, firstMatrix, secondMatrix, resultMatrix);
    }
#ifdef DEBUG
    log("consumer #" + to_string(numberOfConsumer) + " has finished");
#endif
}


void scheduleProducersAndConsumers(int producerAmount, int consumerAmount, Matrix& firstMatrix, Matrix& secondMatrix, Matrix& resultMatrix) {
    ThreadSafeQueue queue;
    vector<thread> producers;
    vector<thread> consumers;
    producers.reserve(producerAmount);
    consumers.reserve(consumerAmount);


    int itemsAmount = MATRIX_SIZE * MATRIX_SIZE;
    int itemsPerProducer = itemsAmount / producerAmount + (itemsAmount % producerAmount != 0);
    for (int i = 0; i < producerAmount; i++) {
        producers.emplace_back(createProducerTask, std::ref(queue), i + 1, i * itemsPerProducer,
                               (i == producerAmount - 1 ? itemsAmount - (producerAmount - 1) * itemsPerProducer
                                                        : itemsPerProducer),
                               MATRIX_SIZE);
    }
#ifdef DEBUG
    log("producers scheduled");
#endif

    int itemsPerConsumer = itemsAmount / consumerAmount + (itemsAmount % consumerAmount != 0);
    for (int i = 0; i < consumerAmount; i++) {
        consumers.emplace_back(createConsumerTask, std::ref(queue), i + 1, std::ref(firstMatrix),
                               std::ref(secondMatrix),
                               std::ref(resultMatrix),
                               (i == consumerAmount - 1 ? itemsAmount - (consumerAmount - 1) * itemsPerConsumer
                                                        : itemsPerConsumer));
    }
#ifdef DEBUG
    log("consumers scheduled");
#endif

    for (auto &&thread: producers) {
        thread.join();
    }
#ifdef DEBUG
    log("producers' join completed");
#endif

    for (auto &&thread: consumers) {
        thread.join();
    }
#ifdef DEBUG
    log("consumers' join completed");
#endif

#ifdef DEBUG
    for (int i = 0; i < resultMatrix.size(); i++)
    {
        for (int j = 0; j < resultMatrix[i].size(); j++)
        {
            cout << resultMatrix[i][j] << ' ';
        }
        cout << '\n';
    }
#endif
}

long long makeExperiment(int producerAmount, int consumerAmount, int experimentsAmount) {
    log("experiment started with " + to_string(producerAmount) + " producers and " + to_string(consumerAmount) +
        " consumers, experimentsAmount " + to_string(experimentsAmount));
    vector<long long> durations(experimentsAmount);

    for (int i = 0; i < experimentsAmount; i++) {

        Matrix firstMatrix;
        Matrix secondMatrix;
        Matrix resultMatrix;
        firstMatrix.resize(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
        secondMatrix.resize(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
        resultMatrix.resize(MATRIX_SIZE, vector<int>(MATRIX_SIZE));

        MatrixUtils::fillMatrix(firstMatrix);
        MatrixUtils::fillMatrix(secondMatrix);

        auto startTime = chrono::high_resolution_clock::now();
        scheduleProducersAndConsumers(producerAmount, consumerAmount, firstMatrix, secondMatrix, resultMatrix);
        auto finishTime = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
        durations[i] = duration.count();
    }
    long long durationsSum = 0;
    for (int i = 0; i < durations.size(); i++) {
        durationsSum += durations[i];
    }


    return ((long long) durationsSum) / experimentsAmount;
}

int main() {
    cout << makeExperiment(MAX_PRODUCERS_SIZE, MAX_CONSUMERS_SIZE, EXPERIMENTS_AMOUNT) << '\n';
}
