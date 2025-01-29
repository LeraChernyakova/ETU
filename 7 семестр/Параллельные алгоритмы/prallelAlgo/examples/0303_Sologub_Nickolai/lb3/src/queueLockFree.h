#ifndef QUEUELOCKFREE_H
#define QUEUELOCKFREE_H
#include "matrix.h"
#include <iostream>
#include <atomic>
#include <thread>

class QueueLockFree{
private:
    struct Node {
        Matrix data;
        std::atomic<Node*> next;

        Node() : data(Matrix()), next(nullptr) {}
        Node(const Matrix& matrix) : data(matrix), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;
public:
    QueueLockFree();
    void produce(const Matrix& matrix);
    bool consume(Matrix& value);
};
 #endif // QUEUELOCKFREE_H