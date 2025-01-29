#ifndef THIN_THREADS_QUEUE 
#define THIN_THREADS_QUEUE 

#include <mutex>

#include "base_threads_queue.h"


template<typename T>
class thinThreadsQueue: public baseThreadsQueue<T> {
    private:
        struct node {
            std::shared_ptr<T> data;
            std::unique_ptr<node> next;
        };

        std::unique_ptr<node> head;
        node* tail;

        std::mutex headMutex;
        std::mutex tailMutex;

    public:
        thinThreadsQueue(int maxSize): baseThreadsQueue<T>(maxSize) {
            head = std::make_unique<node>();
            tail = head.get();
        }

        thinThreadsQueue(const thinThreadsQueue& other) = delete;
        thinThreadsQueue& operator=(const thinThreadsQueue& other) = delete;

        void push(T newValue) {
            std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
            std::unique_ptr<node> p(new node);

            {
                std::unique_lock<std::mutex> lock(tailMutex);
                this->fullCv.wait(lock, [&] {return this->size.load() < this->maxSize.load();});

                tail->data = newData;
                node* const newTail = p.get();
                tail->next = std::move(p);
                tail = newTail;
                this->size++;
            }

            this->emptyCv.notify_one();
        }

        std::shared_ptr<T> pop() {
            std::unique_lock<std::mutex> headLock(headMutex);
            this->emptyCv.wait(headLock, [&] {return head.get() != get_tail();});

            std::unique_ptr<node> oldHead = std::move(head);
            head = std::move(oldHead->next);
            this->size--;

            this->fullCv.notify_one();
            return oldHead->data;
        }

    private:
        node* get_tail() {
            std::lock_guard<std::mutex> tailLock(tailMutex);
            return tail;
        }
};

#endif