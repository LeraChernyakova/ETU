#ifndef ROUGH_THREADS_QUEUE 
#define ROUGH_THREADS_QUEUE 

#include <mutex>

#include "base_threads_queue.h"


template<typename T>
class roughThreadsQueue: public baseThreadsQueue<T> {
    private:
        struct node {
            std::shared_ptr<T> data;
            std::unique_ptr<node> next;
        };

        std::unique_ptr<node> head;
        node* tail;

        std::mutex globalMutex;

    public:
        roughThreadsQueue(int maxSize): baseThreadsQueue<T>(maxSize) {
            head = std::make_unique<node>();
            tail = head.get();
        }

        roughThreadsQueue(const roughThreadsQueue& other) = delete;
        roughThreadsQueue& operator=(const roughThreadsQueue& other) = delete;

        void push(T newValue) {
            std::unique_lock<std::mutex>lock(globalMutex);
            this->fullCv.wait(lock, [&] {return this->size.load() < this->maxSize.load();});
            
            std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
            std::unique_ptr<node> p(new node);

            tail->data = newData;
            node* const newTail = p.get();
            tail->next = std::move(p);
            tail = newTail;
            this->size++;

            this->emptyCv.notify_one();
        }

        std::shared_ptr<T> pop() {
            std::unique_lock<std::mutex> lock(globalMutex);
            this->emptyCv.wait(lock, [&] {return head.get() != tail;});

            std::unique_ptr<node> oldHead = std::move(head);
            head = std::move(oldHead->next);
            this->size--;

            this->fullCv.notify_one();
            return oldHead->data;
        }
};

#endif