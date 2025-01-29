//
// Created by mikeasta on 11/5/23.
//
#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

template <typename T>
class HardBlockingQueue {
private:
    std::queue<T> tasksQueue;
    std::condition_variable conditionVariable;
    std::mutex queueMutex;
public:
    void push(T task) {
        std::unique_lock<std::mutex> ul(queueMutex);
        tasksQueue.push(task);
        //log("Pushed to hard-blocked queue. Queue length is " + std::to_string(tasksQueue.size()));
        conditionVariable.notify_one();
    }

    std::shared_ptr<T> popWithWaiting() {
        std::unique_lock<std::mutex> ul(queueMutex);
        std::shared_ptr<T> ans = nullptr;

        // Wait for element in queue
        conditionVariable.wait(ul, [this](){ return !this->tasksQueue.empty();});
        ans = std::make_shared<T>(move(tasksQueue.front()));
        tasksQueue.pop();

        //log("Waited and popped from hard-blocked queue. Queue length is " + std::to_string(tasksQueue.size()));
        return ans;
    }
};