#ifndef THIN_THREADS_QUEUE 
#define THIN_THREADS_QUEUE 

#include <mutex>
#include <iostream>

#include "base_threads_queue.h"


template<class T>
class thinThreadsQueue: public baseThreadsQueue<T> {     
    private:
        std::mutex pushLock;
        std::mutex popLock;

    public:
        thinThreadsQueue(int maxSize): baseThreadsQueue<T>(maxSize) {}

        void push(T& value) {
            std::unique_lock<std::mutex> ul(this->pushLock);
            this->fullCv.wait(ul, [&]() {return (this->queue.size() != this->maxSize);});

            this->queue.push(value);

            ul.unlock();
            this->emptyCv.notify_one();
        };

        T pop() {
            std::unique_lock<std::mutex> ul(this->popLock);
            this->emptyCv.wait(ul, [&]() {return (this->queue.size() != 0);});

            T element = this->queue.front();
            this->queue.pop();

            ul.unlock();
            this->fullCv.notify_one();
            return element;
        }
};

#endif