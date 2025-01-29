#include <atomic>
#include <memory>
#include <utility>
#include <chrono>

using namespace std;

template<typename T>
class lockfree_queue {
    struct Node {
        shared_ptr<T> data;
        atomic<Node*> next = nullptr;
    };

    atomic<Node*> head;
    atomic<Node*> tail;
public:
    lockfree_queue()
        : head(new Node()), tail(head.load()) {}

    void add(T element) {
        Node* new_node = new Node();
        new_node->data = make_shared<T>(move(element));
        while (true) {
            Node* last = tail.load();
            Node* next = last->next.load();
            if (last == tail.load()) {
                if (next == nullptr) {
                    if (last->next.compare_exchange_weak(next, new_node)) {
                        tail.compare_exchange_weak(last, new_node);
                        return;
                    }
                } else {
                    tail.compare_exchange_weak(last, next);
                }
            }

        }
    }

    bool get(T& element) {
        while (true) {
            Node* first = head.load();
            Node* last = tail.load();
            Node* next = first->next.load();
            if (first == last) {
                if (next == nullptr) {
                    return false;
                }
                tail.compare_exchange_weak(last, next);
            } else {
                if (head.compare_exchange_weak(first, next)) {
                    element = move(*next->data.get());
                    return true;
                }
            }
        }

    }

    ~lockfree_queue() {
        Node* cur = head.load();
        Node* tmp;
        while (cur) {
            tmp = cur;
            cur = cur->next;
            delete tmp;
        }

    }

};
