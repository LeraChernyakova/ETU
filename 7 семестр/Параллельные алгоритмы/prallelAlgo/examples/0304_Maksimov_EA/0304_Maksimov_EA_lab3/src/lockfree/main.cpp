#include <iostream>
#include <queue>
#include <thread>

#include "../io/input.h"
#include "../model/matrix.h"
#include "LockFreeQueue.h"

LockFreeQueue buffer;

void producer(int countIterations) {
    for (int i = 0; i < countIterations; i++) {
        buffer.push();
    }
}

void consumer(int countIterations) {
    for (int i = 0; i < countIterations; i++) {
        Matrix popMatrix;
        while(!buffer.pop(popMatrix)) {}        // Пока не получится извлечь
        popMatrix = squareMatrix(popMatrix);
    }
}

int main() {
    std::vector<int> inputValues = readInputFile();
    if(inputValues.size() != 3) {
        return -1;
    }

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

    return 0;
}
