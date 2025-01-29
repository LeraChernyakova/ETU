#ifndef NON_LOCK_THREADS_QUEUE 
#define NON_LOCK_THREADS_QUEUE 

#include <atomic>

#include "base_threads_queue.h"


template<typename T>
class nonLockThreadsQueue: public baseThreadsQueue<T> {
    private:
        struct node {
            std::shared_ptr<T> data;
            std::atomic<node*> next;
        };

        std::atomic<node*> head;
        std::atomic<node*> tail;

        std::atomic<node*> to_be_deleted;
        std::atomic<unsigned> threads_in_pop;

    public:
        nonLockThreadsQueue(int maxSize): baseThreadsQueue<T>(maxSize) {
            head.store(new node());
            tail = head.load();
        }

        nonLockThreadsQueue(const nonLockThreadsQueue& other) = delete;
        nonLockThreadsQueue& operator=(const nonLockThreadsQueue& other) = delete;

        void push(T newValue) {
            node *t, *n;
            node* w = new node();
            w->data = std::make_shared<T>(std::move(newValue));
            for (;;) {
                if (this->size.load() < this->maxSize.load()) {
                    t = tail.load();
                    n = t->next.load();
                    // Консистентность t и tail.
                    if (t == tail.load()) {
                        // Указывает ли хвост на последний элемент до сих пор.
                        if (!n) {
                            if (t->next.compare_exchange_weak(n, w)) {
                                tail.compare_exchange_weak(t, w);
                                this->size++;
                                return;
                            }
                        } else {
                            // Хвост не указывает на последний элемент.
                            // Механизм помощи.
                            tail.compare_exchange_weak(t, n);
                        }
                    }
                }
            }
        }

        std::shared_ptr<T> pop() {
            node *f, *t, *n;
            threads_in_pop++;
            for (;;) {
                f = head.load();
                t = tail.load();
                n = f->next.load();
                // Консистентность f и head.
                if (f == head.load()) {
                    // Очередь пуста или хвост не успел обновиться.
                    if (f == t) {
                        // Если очередь не пуста.
                        if (n) {
                            // Хвост не указывает на последний элемент.
                            tail.compare_exchange_weak(t,  n);
                        }
                    } else {
                        std::shared_ptr<T> ret = n->data;
                        // Пытаемся перенести голову.
                        if (head.compare_exchange_weak(f, n)) {
                            try_reclaim(f);
                            this->size--;
                            return ret;
                        }
                    }
                }
            }
        }

    private:
        static void delete_nodes(node* nodes) {
            while(nodes) {
                node* next=nodes->next;
                delete nodes;
                nodes=next;
            }
        }

        void try_reclaim(node* old_head) {
            if (threads_in_pop == 1) {
                // Предъявляем права на список.
                node* nodes_to_delete = to_be_deleted.exchange(nullptr);

                if(!--threads_in_pop) {
                    delete_nodes(nodes_to_delete);
                } else if(nodes_to_delete) {
                    chain_pending_nodes(nodes_to_delete);
                }
                // Удаляем только что переданный узел, так как мы были последние в pop.
                delete old_head;
            } else {
                chain_pending_node(old_head);
                --threads_in_pop;
            }
        }

        void chain_pending_nodes(node* nodes) {
            // Ищем последний элемент списка.
            node* last = nodes;
            while(node* const next=last->next) {
                last = next;
            }
            chain_pending_nodes(nodes, last);
        }

        void chain_pending_nodes(node* first, node* last) {
            // Заново отправляем список не очищенных node-ов на удаление.
            last->next.store(to_be_deleted.load());
            node* l_n = last->next.load();
            while(!to_be_deleted.compare_exchange_weak(l_n, first));
        }

        void chain_pending_node(node* n) {
            // Особый случай, добавляем 1 элемент в to_be_deleted;
            chain_pending_nodes(n, n);
        }
};

#endif