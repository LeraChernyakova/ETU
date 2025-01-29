//
// Created by mikeasta on 11/15/23.
//
#pragma once

#include <atomic>
#include <memory>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::atomic<Node*> next;

        Node(): next(nullptr) {}
        explicit  Node(T data): next(nullptr), data(std::make_shared<T>(data)) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue(): head(new Node), tail(head.load()) {}

    void push(T data) {
        auto newNode = new Node(data);
        while (true) {
            auto oldTail = tail.load();
            auto next    = oldTail->next.load();
            if (!next) {
                if (oldTail->next.compare_exchange_weak(next, newNode)) {
                    tail.compare_exchange_weak(oldTail, newNode);
                    return;
                } else {
                    tail.compare_exchange_weak(oldTail, oldTail->next);
                }
            }
        }
    }

    std::shared_ptr<T> pop() {
        while(true) {
            auto oldHead = head.load();
            auto oldTail = tail.load();
            auto nextHead = oldHead->next.load();

            if (oldHead == oldTail) {
                if (!nextHead) return nullptr;
                tail.compare_exchange_weak(oldTail, nextHead);
            } else {
                std::shared_ptr<T> ans = nextHead->data;
                if (head.compare_exchange_weak(oldHead, nextHead)) return ans;
            }
        }
    }
};
