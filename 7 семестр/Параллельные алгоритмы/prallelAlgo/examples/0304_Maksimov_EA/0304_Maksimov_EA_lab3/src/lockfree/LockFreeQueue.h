#pragma once

#include <atomic>

#include "../model/matrix.h"

// #define DEBUG

class Node {
public:
    Matrix data;
    std::atomic<Node*> next;

    Node();
    ~Node();
};

class LockFreeQueue {
private:
	std::atomic<Node*> nodeHead;
	std::atomic<Node*> nodeTail;

public:
    LockFreeQueue();
    ~LockFreeQueue();
    
    void push();
    bool pop(Matrix& matrix);
};
