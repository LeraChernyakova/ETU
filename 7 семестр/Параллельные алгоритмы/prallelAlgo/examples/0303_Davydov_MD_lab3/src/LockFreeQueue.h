#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H
#include "matrix.h"
#include <iostream>
#include <atomic>
#include <thread>

class LockFreeQueue{
private:
    struct Node 
    {
        Matrix data;
        std::atomic<Node*> next;

        Node() : data(Matrix()), next(nullptr) 
        {

        }

        Node(const Matrix& matrix) : data(matrix), next(nullptr) 
        {

        }
    };
public:
    LockFreeQueue();
    void push(const Matrix& matrix);
    bool pop(Matrix& value);

private:
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
};
 #endif // LOCKFREEQUEUE_H
