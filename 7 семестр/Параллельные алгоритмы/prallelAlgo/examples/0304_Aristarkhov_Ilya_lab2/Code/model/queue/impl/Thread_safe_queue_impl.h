#ifndef PA_LAB_2_THREAD_SAFE_QUEUE_IMPL_H
#define PA_LAB_2_THREAD_SAFE_QUEUE_IMPL_H

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "../Thread_safe_queue.h"

template<typename T>
class Thread_safe_queue_impl : public Thread_safe_queue<T> {
public:
    Thread_safe_queue_impl() = default;

    Thread_safe_queue_impl(const Thread_safe_queue_impl &other) = delete;

    Thread_safe_queue_impl &operator=(const Thread_safe_queue_impl &other) = delete;

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock lk(mutex);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    void push(T new_value) {
        std::lock_guard lk(mutex);
        data_queue.push(new_value);
        data_cond.notify_one();
    }


private:
    mutable std::mutex mutex;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
};

#endif //PA_LAB_2_THREAD_SAFE_QUEUE_IMPL_H
