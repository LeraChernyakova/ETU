#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue {
    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable condVar;
        bool prodEnd = false;

    public:
        void push(const T& data) {
            {
                std::unique_lock<std::mutex> guard(mutex);
                queue.push(data);
            }
            condVar.notify_one();
        }
 
        bool pop(T& data) {
            std::unique_lock<std::mutex> guard(mutex);
            condVar.wait(guard, [this](){
                return !queue.empty() || prodEnd;
            });
            if (!queue.empty()) {
                data = queue.front();
                queue.pop();
                return true;
            }
            return false;
        }

        void setEnd() {
            {
                std::unique_lock<std::mutex> guard(mutex);
                prodEnd = true;
            }
            condVar.notify_all();
        }
};
