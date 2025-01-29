#ifndef QUEUEROUGHLOCK_H
#define QUEUEROUGHLOCK_H
#include "matrix.h"
#include <queue>
#include <mutex>
#include <condition_variable>
class QueueRoughLock{
private:
 mutable std::mutex mut; // мьютекс
 std::queue<Matrix> queue; // очередь
 std::condition_variable consumed; // condition_variable

public:
 QueueRoughLock();
 Matrix consume();
 void produce(Matrix& matrix);
};

 #endif // QUEUEROUGHLOCK_H