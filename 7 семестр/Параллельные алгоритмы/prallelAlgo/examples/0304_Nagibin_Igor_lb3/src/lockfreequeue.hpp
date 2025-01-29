#ifndef LAB3_LOCKFREEQUEUE_H
#define LAB3_LOCKFREEQUEUE_H
#include <atomic>
#include <optional>

template<typename T>
class MyLockFreeQueue
{
private:

    struct Node{
        T data;
        std::atomic<Node*> next;
        Node() : next(nullptr){}
        explicit Node(T data) : data(data), next(nullptr){}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:

    MyLockFreeQueue(){
        auto node = new Node();
        head.store(node);
        tail.store(node);
    }

    void push(T item){
        auto newData = new Node(item);
        while (true) {
            auto oldTail = tail.load();
            auto next = oldTail->next.load();
            if (oldTail == tail.load()) {
                if (next == nullptr) {
                    if (oldTail->next.compare_exchange_weak(next, newData)) {
                        tail.compare_exchange_weak(oldTail, newData);
                        break;
                    }
                } else {
                    tail.compare_exchange_weak(oldTail, next);
                }
            }
        }
    }

    std::optional<T> pop(){
        while (true) {
            auto oldHead = head.load();
            auto oldTail = tail.load();
            auto next = oldHead->next.load();
            if (oldHead == oldTail) {
                if (next == nullptr) {
                    return std::nullopt;
                }
                tail.compare_exchange_weak(oldTail, next);
            } else {
                if (head.compare_exchange_weak(oldHead, next)) {
                    std::optional<T> res(oldHead->data);
                    delete oldHead;
                    return res;
                }
            }
        }
    }
};
#endif 