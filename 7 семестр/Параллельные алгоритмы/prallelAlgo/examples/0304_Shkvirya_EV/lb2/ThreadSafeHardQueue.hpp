#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>

using namespace std;

template <typename T>
class ThreadSafeHardQueue
{
private:
    queue<T> tasksQueue;
    condition_variable condVar;
    mutex mutexQueue;
public:

    void push(T task) {
        lock_guard<mutex> lock(mutexQueue);
        tasksQueue.push(task);
        #ifdef DEBUG
        log("out push, taskQueue size = " + to_string(tasksQueue.size()));
        #endif

        condVar.notify_one();
    }

    shared_ptr<T> popWithWaiting() {
        shared_ptr<T> result = nullptr;
        unique_lock<mutex> lock (mutexQueue);

        condVar.wait(lock, [this](){return !this->tasksQueue.empty();});
        result = make_shared<T>(move(tasksQueue.front()));
        tasksQueue.pop();

        #ifdef DEBUG
        log("out popWithWaiting, taskQueue size = " + to_string(tasksQueue.size()));
        #endif

        return result;
    }
};