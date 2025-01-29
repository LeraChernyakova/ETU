#include "ThinQueue.h"

Node::Node() {
    this->data = generateMatrix();
    this->next = nullptr;
}

Node::~Node() {}

ThinQueue::ThinQueue() {
    Node* newNode = new Node;
    this->nodeHead = newNode;
    this->nodeTail = newNode;
}

ThinQueue::~ThinQueue() {}

void ThinQueue::push() {
    std::unique_lock<std::mutex> lock(this->mtxTail);
    #ifdef DEBUG
        std::cout << "Add started ";
    #endif
    Node* pushNode = new Node;
    this->nodeTail->next = pushNode;    // Указатель хвостового элемента
    this->nodeTail = pushNode;          // Указатель на хвост в ThinQueue
    #ifdef DEBUG
        std::cout << "Add finished" << std::endl;
    #endif
    cv.notify_one();
}

Matrix ThinQueue::pop() {
    std::unique_lock<std::mutex> lock(this->mtxHead);
    cv.wait(lock, [this]{
        return this->nodeHead != this->getTail();
    });
    #ifdef DEBUG
        std::cout << "Delete started ";
    #endif
    Node* popNode = this->nodeHead;         // Достаём головной элемент
    this->nodeHead = this->nodeHead->next;  // Указатель на голову в ThinQueue
    #ifdef DEBUG
        std::cout << "Delete finished" << std::endl;
    #endif
    return popNode->data;
}

Node* ThinQueue::getTail() {
    std::unique_lock<std::mutex> lock(this->mtxTail);
	return this->nodeTail;
}
