#ifndef BASE_THREADS_QUEUE 
#define BASE_THREADS_QUEUE 

#include <queue>
#include <condition_variable>


template<class T>
class baseThreadsQueue {
    protected:
        int maxSize;
        std::queue<T> queue;

        std::condition_variable emptyCv;
        std::condition_variable fullCv;
    
    public:
        baseThreadsQueue(int maxSize) {this->maxSize = maxSize;};

        virtual void push(T&) = 0;
        virtual T pop() = 0;
};

#endif