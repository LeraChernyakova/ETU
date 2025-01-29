#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

#define QUEUE_SIZE 10

template <typename T>

class Queue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable in;
	std::condition_variable out;

public:
    void push(const T& data) {
        std::unique_lock<std::mutex> guard(mutex);
        in.wait(guard, [&] {
            return queue.size() < QUEUE_SIZE;
        });
        queue.push(data);
        out.notify_one();
    }

    bool pop(T& data) {
        std::unique_lock<std::mutex> guard(mutex);
        out.wait(guard, [this](){
            return !queue.empty();
        });
        if (!queue.empty()) {
            data = queue.front();
            queue.pop();
			in.notify_one();
            return true;
        }
        return false;
    }
};