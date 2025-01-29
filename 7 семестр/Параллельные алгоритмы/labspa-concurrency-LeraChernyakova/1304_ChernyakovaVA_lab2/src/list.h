#pragma once
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

#define QUEUE_SIZE 10

template <typename T>

class List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head;
    Node *tail;
    std::mutex mutexHead;
    std::mutex mutexTail;
    std::condition_variable out;
    std::condition_variable in;
    int size = 0;

    Node *getLockedTail() {
        std::unique_lock<std::mutex> guard(mutexTail);
        return tail;
    }

public:
    List(): head{std::make_unique<Node>()}, tail{head.get()} {}

    void push(const T& data) {
        std::unique_lock<std::mutex> guard(mutexTail);
        in.wait(guard, [this]() {
            return size < QUEUE_SIZE;
        });

        tail->data = data;
        tail->next = std::make_unique<Node>();
        tail = tail->next.get();
        size++;

        out.notify_one();
    }

    bool pop(T& data) {
        std::unique_lock<std::mutex> guard(mutexHead);
        out.wait(guard, [this](){
            return head.get() != getLockedTail();
        });
        if (head.get() != getLockedTail()) {
            data = head->data;
            head = std::move(head->next);
            size--;
            in.notify_one();
            return true;
        }
        return false;
    }
};
