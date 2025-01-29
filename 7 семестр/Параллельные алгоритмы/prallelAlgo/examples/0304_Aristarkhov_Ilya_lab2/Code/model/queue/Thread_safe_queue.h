#ifndef PA_LAB_2_THREAD_SAFE_QUEUE_H
#define PA_LAB_2_THREAD_SAFE_QUEUE_H

#include <memory>

template<typename T>
class Thread_safe_queue {
public:
    virtual std::shared_ptr<T> wait_and_pop() = 0;

    virtual void push(T new_value) = 0;
};


#endif //PA_LAB_2_THREAD_SAFE_QUEUE_H
