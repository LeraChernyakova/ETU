#ifndef THINLOCK_H
#define THINLOCK_H
#include "matrix.h"
#include <mutex>
#include <memory>
#include <condition_variable>

class ThinLock{
private:
struct node
{
    std::shared_ptr<Matrix> data; 
    std::unique_ptr<node> next; 
};

node* get_tail()
{
    std::lock_guard<std::mutex> tail_lock(tail_mutex); 
    return tail; 
}

std::unique_ptr<node> pop_head()
{
    std::unique_lock<std::mutex> head_lock(head_mutex); 
    isEmpty.wait(head_lock, [this](){return head.get()!=get_tail();}); // ждем пока в очереди что-то появится
    std::unique_ptr<node> old_head=std::move(head); 
    head=std::move(old_head->next); 
    return old_head;
}

public:
    ThinLock();
    ThinLock(const ThinLock& other)=delete;
    ThinLock& operator=(const ThinLock& other)=delete;
    Matrix consume();
    void produce(Matrix new_value);

private:
    std::mutex head_mutex; 
    std::unique_ptr<node> head; 
    std::mutex tail_mutex;
    node* tail;
    std::condition_variable isEmpty; 
};
 #endif // THINLOCK_H
