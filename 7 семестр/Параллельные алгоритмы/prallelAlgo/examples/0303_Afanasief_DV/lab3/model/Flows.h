#ifndef LAB2_FLOWS_H
#define LAB2_FLOWS_H
#include <utility>
#include <fstream>
#include <algorithm>
#include "Matrix.h"
#include "MultiplicationMatrix.h"
#include "../queue/queue.h"

class Flows {
public:
    void reader();
    void multiplier();
    void writer();
    Flows(int iterations, int consumers, int producers);
    void run();
private:
    int iterationsConsumer;
    int iterationsProducer;
    const int sizeMatrix = 512;
    const int consumers, producers;
    const int threads = 30;
    LockFreeQueue<Matrix> queueResult;
    LockFreeQueue<std::pair<Matrix, Matrix>> queueMatrix;
};


#endif //LAB2_FLOWS_H
