#ifndef LAB3_LOCKFREEQUEUE_H
#define LAB3_LOCKFREEQUEUE_H
#include <atomic>
#include <optional>

template<typename T>
class LockFreeQueue
{
private:

    struct Node{
        T data;
        std::atomic<Node *> next;
        Node() : next(nullptr){}
        explicit Node(T data) : data(data), next(nullptr){}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:

    LockFreeQueue(){
        Node* node = new Node();
        head.store(node);
        tail.store(node);
    }

    void push(T data){
        Node* newData = new Node(data);
        while (true) {
            Node* last = tail.load();
            Node* next = last->next.load();
            if (last == tail.load()) {
                if (next == nullptr) {
                    if (last->next.compare_exchange_weak(next, newData)) {
                        tail.compare_exchange_weak(last, newData);
                        break;
                    }
                } else {
                    tail.compare_exchange_weak(last, next);
                }
            }
        }
    }

    std::optional<T> pop(){
        while (true) {
            Node* first = head.load();
            Node* last = tail.load();
            Node* next = first->next.load();
            if (first == last) {
                if (next == nullptr) {
                    return std::nullopt;
                }
                tail.compare_exchange_weak(last, next);
            } else {
                if (head.compare_exchange_weak(first, next)) {
                    std::optional<T> res(first->data);
                    delete first;
                    return res;
                }
            }
        }
    }
};
#endif //LAB3_LOCKFREEQUEUE_H
