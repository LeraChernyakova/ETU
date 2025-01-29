//
// Created by mikeasta on 11/5/23.
//
#pragma once

#include <mutex>
#include <condition_variable>
#include <memory>

template<typename T>
class FineBlockingQueue {
private:
    struct Node {
        std::shared_ptr<T> value;
        Node* next;
    };

    std::mutex headMutex;
    std::mutex tailMutex;

    Node* head = nullptr;
    Node* tail = nullptr;

    std::condition_variable conditionVariable;

    Node* getTail() {
        std::lock_guard<std::mutex> lock(tailMutex);
        return tail;
    }

public:
    FineBlockingQueue(): head(new Node), tail(head) {}

    void push(T task) {
        std::unique_lock<std::mutex> ul(tailMutex, std::defer_lock);
        std::shared_ptr<T> newData = std::make_shared<T>(move(task));
        Node* newNode = new Node;

        ul.lock();
        tail->value   = newData;
        Node* newTail = newNode;
        tail->next    = std::move(newNode);
        tail          = newTail;
        ul.unlock();

        conditionVariable.notify_one();
    }

    std::shared_ptr<T> popWithWaiting() {
        std::unique_lock<std::mutex> lock(headMutex);
        conditionVariable.wait(lock, [this]() { return this->head != this->getTail(); });
        Node* oldHead = std::move(head);
        head = std::move(oldHead->next);
        return std::make_shared<T>(*(oldHead->value));
    }
};