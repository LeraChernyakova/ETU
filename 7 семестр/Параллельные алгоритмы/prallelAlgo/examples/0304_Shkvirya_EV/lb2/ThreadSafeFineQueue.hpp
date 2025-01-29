#pragma once

#include <condition_variable>
#include <mutex>
#include <memory>

using namespace std;

template<typename T>
class ThreadSafeFineQueue {
private:
    struct QueueNode
    {
        shared_ptr<T> value;
        unique_ptr<QueueNode> next;
    };

    mutex headMutex;
    unique_ptr<QueueNode> head = nullptr;
    mutex tailMutex;
    QueueNode* tail = nullptr;

    condition_variable condVar;

    QueueNode* getTail() {
        lock_guard<mutex> lock(tailMutex);
        return tail;
    }

public:
    ThreadSafeFineQueue(): head(new QueueNode), tail(head.get()) {}
    ThreadSafeFineQueue(const ThreadSafeFineQueue&)=delete;
    ThreadSafeFineQueue& operator=(const ThreadSafeFineQueue&) = delete;

    void push(T task) {
        shared_ptr<T> newData = make_shared<T>(move(task));
        unique_ptr<QueueNode> newNode = make_unique<QueueNode>();
        {
            lock_guard<mutex> lock(tailMutex);
            tail->value = newData;
            QueueNode* newTail = newNode.get();
            tail->next = move(newNode);
            tail = newTail;

            #ifdef DEBUG
            log("out push");
            #endif
        }
        condVar.notify_one();
    }

    shared_ptr<T> popWithWaiting() {
        unique_lock<mutex> lock(headMutex);
        condVar.wait(lock, [this]() { return this->head.get() != this->getTail(); });
        unique_ptr<QueueNode> oldHead = move(head);
        head = move(oldHead->next);

        #ifdef DEBUG
        log("out popWithWaiting");
        #endif
        return make_shared<T>(*(oldHead->value));
    }
};