#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

#include <atomic>
#include <vector>
#include <unordered_set>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;
    };

    struct ThreadInfo {
        std::atomic<Node*> hp1;
        std::atomic<Node*> hp2;
        std::vector<Node*> dlist;
        int dcount = 0;
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    std::vector<ThreadInfo> threadsInfo;

    void deleteRecursive(Node* elem) {
        if (elem) {
            deleteRecursive(elem->next);
            delete elem;
        }
    }

    void retire(int threadNum, Node* ptrToDelete) {
        auto& current_thread = threadsInfo[threadNum];
        current_thread.dlist[current_thread.dcount++] = ptrToDelete;
        if (current_thread.dcount == current_thread.dlist.size()) {
            scan(threadNum);
        }
    }

    void scan(int threadNum) {
        std::unordered_set<Node*> hps;
        for (const auto& info : threadsInfo) {
            hps.insert(info.hp1);
            hps.insert(info.hp2);
        }
        auto& myDlist = threadsInfo[threadNum].dlist;
        int newDcount = 0;
        for (auto& node : myDlist) {
            if (hps.count(node)) {
                myDlist[newDcount++] = node;
            } else {
                delete node;
            }
        }
        threadsInfo[threadNum].dcount = newDcount;
    }

public:
    explicit LockFreeQueue(int threadCount) : threadsInfo(threadCount) {
        Node* dummy = new Node;
        head = dummy;
        tail = dummy;
        for (auto& ti : threadsInfo) {
            ti.dlist.resize(4 * threadCount);
        }
    }

    ~LockFreeQueue() {
        Node* node = head.load();
        while (node) {
            Node* next = node->next.load();
            delete node;
            node = next;
        }
    }

    void push(const T& data, int threadNum) {
        Node* newTail = new Node{data};
        while (true) {
            Node* tail_ = tail.load();
            threadsInfo[threadNum].hp1.store(tail_);
            if (tail_ != tail.load()) continue;
            Node* tmp = nullptr;
            if (tail_->next.compare_exchange_strong(tmp, newTail)) {
                tail.compare_exchange_strong(tail_, newTail);
                break;
            }
            tail.compare_exchange_strong(tail_, tail_->next.load());
        }
        threadsInfo[threadNum].hp1.store(nullptr);
    }

    bool pop(T& data, int threadNum) {
        while (true) {
            Node* head_ = head.load();
            threadsInfo[threadNum].hp1.store(head_);
            if (head_ != head.load()) continue;
            Node* nextHead = head_->next.load();
            threadsInfo[threadNum].hp2.store(nextHead);
            if (nextHead != head_->next.load()) continue;

            if (!nextHead) {
                threadsInfo[threadNum].hp1.store(nullptr);
                return false;
            }

            if (head_ == tail.load()) {
                Node* expected = tail.load();
                tail.compare_exchange_strong(expected, nextHead);
            } else if (head.compare_exchange_strong(head_, nextHead)) {
                data = nextHead->data;
                threadsInfo[threadNum].hp1.store(nullptr);
                threadsInfo[threadNum].hp2.store(nullptr);
                retire(threadNum, head_);
                break;
            }
        }
        return true;
    }
};

#endif // LOCKFREEQUEUE_H
