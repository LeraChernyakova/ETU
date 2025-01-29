#pragma once
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

template <typename T>
class QueueFine {
    private:
        struct Node {
            T data;
            std::unique_ptr<Node> next;
        };

        std::unique_ptr<Node> head;
        Node *tail;
        std::mutex mutexHead;
        std::mutex mutexTail;
        std::condition_variable condVar;
        bool prodEnd = false;

        Node *getLockedTail() {
            std::unique_lock<std::mutex> guard(mutexTail);
            return tail;
        }

    public:
        QueueFine(): head{std::make_unique<Node>()}, tail{head.get()} {}

        void push(const T& data) {
            {
                std::unique_lock<std::mutex> guard(mutexTail);
                tail->data = data;
                tail->next = std::make_unique<Node>();
                tail = tail->next.get();
            }
            condVar.notify_one();
        }
 
        bool pop(T& data) {
            std::unique_lock<std::mutex> guard(mutexHead);
            condVar.wait(guard, [this](){
                return head.get() != getLockedTail() || prodEnd;
            });
            if (head.get() != getLockedTail()) {
                data = head->data;
                head = std::move(head->next);
                return true;
            }
            return false;
        }

        void setEnd() {
            {
                std::unique_lock<std::mutex> guard(mutexHead);
                prodEnd = true;
            }
            condVar.notify_all();
        }
};
