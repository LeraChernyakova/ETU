#ifndef QUEUETHINLOCK_H
#define QUEUETHINLOCK_H
#include "matrix.h"
#include <mutex>
#include <memory>
#include <condition_variable>

class QueueThinLock{
private:
struct node // узел очереди
{
std::shared_ptr<Matrix> data; // матрица
std::unique_ptr<node> next; // следующий узел
};
std::mutex head_mutex; // мьютекс головы
std::unique_ptr<node> head; // начало очереди - голова
std::mutex tail_mutex; // мьютекс хвоста
node* tail; // указатель на последний узел
std::condition_variable isEmpty; // condition_variable
node* get_tail()
{
std::lock_guard<std::mutex> tail_lock(tail_mutex); // блокируем хвост, чтобы его не поменяли
return tail; // возвращаем хвост
}
std::unique_ptr<node> pop_head() // вытаскиваем голову
{
std::unique_lock<std::mutex> head_lock(head_mutex); // блокируем голову, чтобы её не поменяли
isEmpty.wait(head_lock, [this](){return head.get()!=get_tail();}); // ждём пока в очереди появятся элементы
std::unique_ptr<node> old_head=std::move(head); // перемещаем старую голову
head=std::move(old_head->next); // теперь новая голова
return old_head; // вытаскиваем старую голову
}
public:
QueueThinLock();
QueueThinLock(const QueueThinLock& other)=delete;
QueueThinLock& operator=(const QueueThinLock& other)=delete;
Matrix consume();
void produce(Matrix new_value);
};
 #endif // QUEUETHINLOCK_H