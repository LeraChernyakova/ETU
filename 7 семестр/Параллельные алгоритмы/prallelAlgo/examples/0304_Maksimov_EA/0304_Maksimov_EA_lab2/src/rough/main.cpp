#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "../io/output.h"
#include "../io/input.h"
#include "../model/matrix.h"

// #define DEBUG
// #define WRITE_MODE

std::queue<Matrix> buffer;
std::mutex mtx;
std::condition_variable cv;

void producer(int countIterations) {
    for (int i = 0; i < countIterations; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        #ifdef DEBUG
            std::cout << "Producer start, ";
        #endif
        buffer.push(generateMatrix());
        cv.notify_one();
        #ifdef DEBUG
            std::cout << "Producer leave" << std::endl;
        #endif
    }
}

void consumer(int countIterations) {
    for (int i = 0; i < countIterations; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { 
            return !buffer.empty();
        });
        #ifdef DEBUG
            std::cout << "Consumer start, ";
        #endif
        Matrix data = buffer.front();
        buffer.pop();
        #ifdef WRITE_MODE
            writeMatrixToFile(squareMatrix(data));
        #endif
        #ifdef DEBUG
            std::cout << "Consumer leave" << std::endl;
        #endif
    }
}

int main() {
    std::vector<int> inputValues = readInputFile();
    if(inputValues.size() != 3) {
        return -1;
    }

    #ifdef WRITE_MODE
        openOutputFile();
    #endif

    int countProducers = inputValues[0],
        countConsumers = inputValues[1], 
        countIterationsPerProducer = inputValues[2];
    int countIterationPerConsumer = countIterationsPerProducer*countProducers/countConsumers;

    std::vector<std::thread> threads;

    for(int i = 0; i < countConsumers; i++) {
        threads.push_back(std::thread(consumer, countIterationPerConsumer));
    }
    for(int i = 0; i < countProducers; i++) {
        threads.push_back(std::thread(producer, countIterationsPerProducer));
    }

    for(int i = 0; i < countProducers+countConsumers; i++) {
        threads[i].join();
    }

    #ifdef WRITE_MODE
        closeOutputFile();
    #endif
    return 0;
}
