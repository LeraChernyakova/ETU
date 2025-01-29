#ifndef INC_0304_ARISTARKHOV_ILYA_LAB3_LOCK_FREE_QUEUE_H
#define INC_0304_ARISTARKHOV_ILYA_LAB3_LOCK_FREE_QUEUE_H

#include <memory>
#include <atomic>
#include <thread>
#include <functional>


template<typename T>
class Lock_free_queue {

private:

    struct node {
        std::shared_ptr<T> data;
        std::atomic<node*> next;
    };

    std::atomic<node*> head;
    std::atomic<node*> tail;

    std::atomic<unsigned> threads_in_pop;
    std::atomic<node*> to_be_deleted;

    static void delete_nodes(node* nodes) {
        while(nodes) {
            node* next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void chain_pending_nodes(node* first, node* last)
    {
        last->next.store(to_be_deleted.load());
        node* last_next = last->next.load();
        while(!to_be_deleted.compare_exchange_weak(last_next, first));
    }

    void chain_pending_nodes(node* nodes)
    {
        node* last = nodes;
        while(node* const next = last->next) {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_node(node* n)
    {
        chain_pending_nodes(n, n);
    }

    void try_reclaim(node* old_head) {
        if (threads_in_pop == 1) {
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (!--threads_in_pop) {
                delete_nodes(nodes_to_delete);
            }
            else if (nodes_to_delete) {
                chain_pending_nodes(nodes_to_delete);
            }
            delete old_head;
        } else {
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }

public:
    Lock_free_queue(): head(new node), tail(head.load()) {}
    Lock_free_queue(const Lock_free_queue& other) = delete;
    Lock_free_queue& operator=(const Lock_free_queue& other) = delete;

    ~Lock_free_queue()
    {
        while(node* const old_head = head.load())
        {
            head.store(old_head->next.load());
            delete old_head;
        }
    }

    std::shared_ptr<T> pop() {

        threads_in_pop++;

        while (true) {
            node *old_head = head.load();
            node *cur_tail = tail.load();
            node *next_head = old_head->next.load();


            if (old_head == cur_tail) {

                if (next_head) {
                    tail.compare_exchange_weak(cur_tail, next_head);
                }
            } else {
                std::shared_ptr<T> res = next_head->data;

                if (head.compare_exchange_weak(old_head, next_head)) {
                    try_reclaim(old_head);
                    return std::move(res);
                }
            }

        }
    }

    void push(T new_value) {
        node* new_node = new node();
        new_node->data = std::make_shared<T>(std::move(new_value));

        while (true) {
            node *old_tail = tail.load();
            node *next = old_tail->next.load();
            if (!next) {
                if (old_tail->next.compare_exchange_weak(next, new_node)) {
                    tail.compare_exchange_weak(old_tail, new_node);
                    return;
                }
            } else {
                tail.compare_exchange_weak(old_tail, next);
            }
        }

    }
};


#endif //INC_0304_ARISTARKHOV_ILYA_LAB3_LOCK_FREE_QUEUE_H
