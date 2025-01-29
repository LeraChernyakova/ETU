#ifndef PA_LAB_2_THREAD_SAFE_QUEUE_IMPL_FINE_H
#define PA_LAB_2_THREAD_SAFE_QUEUE_IMPL_FINE_H

#include <memory>
#include <mutex>
#include <condition_variable>
#include "../Thread_safe_queue.h"

template<typename T>
class Thread_safe_queue_impl_fine : public Thread_safe_queue<T> {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<node> head;

    std::mutex tail_mutex;
    node *tail;

    std::condition_variable data_cond;

    node *get_tail() {
        std::lock_guard tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head() {
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock head_lock(head_mutex);
        data_cond.wait(head_lock, [&] { return head.get() != get_tail(); });
        return std::move(head_lock);
    }

    std::unique_ptr<node> wait_pop_head() {
        std::unique_lock head_lock(wait_for_data());
        return pop_head();
    }

public:
    Thread_safe_queue_impl_fine(): head(new node), tail(head.get()) {}

    Thread_safe_queue_impl_fine(const Thread_safe_queue_impl_fine &other) = delete;

    Thread_safe_queue_impl_fine &operator=(const Thread_safe_queue_impl_fine &other) = delete;

    std::shared_ptr<T> wait_and_pop() {
        std::unique_ptr<node> const old_head = wait_pop_head();
        return old_head->data;
    }

    void push(T new_value){
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);

        {
            std::lock_guard tail_lock(tail_mutex);
            tail->data = new_data;
            node* const new_tail = p.get();
            tail->next = std::move(p);
            tail = new_tail;
        }

        data_cond.notify_one();
    }

};

#endif //PA_LAB_2_THREAD_SAFE_QUEUE_IMPL_FINE_H
