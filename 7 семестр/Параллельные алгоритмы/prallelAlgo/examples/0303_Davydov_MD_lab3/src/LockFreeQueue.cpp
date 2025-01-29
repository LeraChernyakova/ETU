#include "LockFreeQueue.h"


LockFreeQueue::LockFreeQueue()
{
    Node* node = new Node();
    head.store(node);
    tail.store(node);
}

void LockFreeQueue::push(const Matrix& matrix)
{
    Node* newNode = new Node(matrix);
    while (true) 
    {
        Node* curTail = tail.load();
        Node* next = curTail->next.load();
        if (curTail == tail.load()) //если хвост еще не обновился
        { 
            if (next == nullptr) 
            { // если текущий все еще последний
                if (curTail->next.compare_exchange_weak(next, newNode)) // добавляем
                { 
                    tail.compare_exchange_weak(curTail, newNode); // если хвост не изменился, то меняем 
                    return;
                } 
            } 
            else 
            { //елси хвост обновили
                tail.compare_exchange_weak(curTail, next); // помогаем обновить хвост
            }
        }
    }
}

bool LockFreeQueue::pop(Matrix& value)
{
    while (true) 
    {
        Node* curHead = head.load();
        Node* curTail = tail.load(); 
        Node* first = curHead->next.load();
        if (curHead == head.load()) 
        {
            if (curHead == curTail)
            {//проверка что только голова и есть
                if (first == nullptr) 
                { //проверка на пустоту
                    return false;
                }
                tail.compare_exchange_weak(curTail, first); // обновить хвост
            } 
            else 
            { //очередь не пустая
                if (head.compare_exchange_weak(curHead, first)) 
                { //обновляем
                    value = curHead->data;
                    delete curHead;
                    // удаление ломается при большой конкуренкции !!!
                    return true;
                }
            }
        }
    }
}
