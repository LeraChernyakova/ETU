//
// Created by dima on 29.09.23.
//

#ifndef LAB2_THREADSAFEQUEUE_H
#define LAB2_THREADSAFEQUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
public:
    void push(T value);
    T pop();
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable isEmpty;
};

template<typename T>
T ThreadSafeQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    isEmpty.wait(lock, [this](){return !queue.empty();});
    T value = queue.front();
    queue.pop();
    return value;
}

template<typename T>
void ThreadSafeQueue<T>::push(T value) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(value);
    isEmpty.notify_one();
}


#endif //LAB2_THREADSAFEQUEUE_H
