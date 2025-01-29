#pragma once

#include <mutex>
#include <memory>
#include <condition_variable>

#include "../model/matrix.h"

// #define DEBUG

class Node {
public:
    Matrix data;
    Node* next;

    Node();
    ~Node();
};

class ThinQueue {
private:
    std::mutex mtxHead;
	std::mutex mtxTail;
	std::condition_variable cv;
	Node* nodeHead;
	Node* nodeTail;

    Node* getTail();

public:
    ThinQueue();
    ~ThinQueue();
    
    void push();
    Matrix pop();
};
