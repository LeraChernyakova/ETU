#ifndef ROUGHLOCK_H
#define ROUGHLOCK_H
#include "matrix.h"
#include <queue>
#include <mutex>
#include <condition_variable>
class RoughLock{
public:
    RoughLock();
    Matrix consume();
    void produce(Matrix& matrix);

private:
    mutable std::mutex mut; 
    std::queue<Matrix> queue;
    std::condition_variable consumed;
};

 #endif // ROUGHLOCK_H
