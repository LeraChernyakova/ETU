#ifndef BASE_THREADS_QUEUE 
#define BASE_THREADS_QUEUE 

#include <condition_variable>
#include <atomic>


template<class T>
class baseThreadsQueue {
    protected:
        std::atomic<int> maxSize;
        std::atomic<int> size = 0;

        std::condition_variable emptyCv;
        std::condition_variable fullCv;
    
    public:
        baseThreadsQueue(int maxSize) {this->maxSize.store(maxSize);};

        virtual void push(T) = 0;
        virtual std::shared_ptr<T> pop() = 0;
};

#endif