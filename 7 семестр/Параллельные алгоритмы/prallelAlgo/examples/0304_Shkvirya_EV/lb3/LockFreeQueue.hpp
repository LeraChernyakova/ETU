#pragma once

#include <atomic>
#include <memory>

using namespace std;

template<typename T>
class LockFreeQueue {
private:
    struct QueueNode {
        shared_ptr<T> data;
        atomic<QueueNode *> next;

        QueueNode() : next(nullptr) {}

        explicit QueueNode(T data) : next(nullptr), data(make_shared<T>(data)) {}

    };

    atomic<QueueNode *> head;
    atomic<QueueNode *> tail;

public:
    LockFreeQueue() : head(new QueueNode()), tail(head.load()) {}

    void push(T data) {
        auto newNode = new QueueNode(data);
        while (true) {
            auto oldTail = tail.load();
            auto next = oldTail->next.load();
            if (!next) {
                if (oldTail->next.compare_exchange_weak(next, newNode)) {
                    tail.compare_exchange_weak(oldTail, newNode);
                    return;
                } else {
                    tail.compare_exchange_weak(oldTail, oldTail->next.load());
                }
            }
        }
    }

    shared_ptr<T> pop() {
        while (true) {
            auto oldHead = head.load();
            auto oldTail = tail.load();
            auto nextHead = oldHead->next.load();

            if (oldHead == oldTail) {
                if (nextHead == nullptr) {
                    return nullptr;
                }
                tail.compare_exchange_weak(oldTail, nextHead);
            } else {
                shared_ptr<T> res = nextHead->data;
                if (head.compare_exchange_weak(oldHead, nextHead)) {
                    return res;
                }
            }
        }
    }
};