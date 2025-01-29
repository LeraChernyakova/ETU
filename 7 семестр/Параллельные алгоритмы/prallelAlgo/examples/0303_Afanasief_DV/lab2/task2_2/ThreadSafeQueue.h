//
// Created by dima on 29.09.23.
//

#ifndef LAB2_THREADSAFEQUEUE_H
#define LAB2_THREADSAFEQUEUE_H
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
public:
    void push(T value){
        std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(value)));
        std::unique_ptr<Node> p(new Node);
        Node* const new_tail=p.get();
        std::lock_guard<std::mutex> tail_lock(tailMutex);
        tail->data=new_data;
        tail->next=std::move(p);
        tail=new_tail;
        isEmpty.notify_one();
    }

    T pop(){
        std::unique_ptr<Node> old_head=popHead();
        return  T(*old_head->data.get());
    }

    ThreadSafeQueue() : head(new Node), tail(head.get()){}
private:
    struct Node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<Node> next;
    };
    std::mutex headMutex;
    std::unique_ptr<Node> head;
    std::mutex tailMutex;
    Node* tail;
    std::condition_variable isEmpty;

    Node* getTail(){
        std::lock_guard<std::mutex> tail_lock(tailMutex);
        return tail;
    }

    std::unique_ptr<Node> popHead(){
        std::unique_lock<std::mutex> head_lock(headMutex);
        isEmpty.wait(head_lock, [this](){return head.get()!=getTail();});
        std::unique_ptr<Node> old_head=std::move(head);
        head=std::move(old_head->next);
        return old_head;
    }
};


#endif //LAB2_THREADSAFEQUEUE_H
