#include "queueLockFree.h"


QueueLockFree::QueueLockFree(){
    Node* node = new Node();
        head.store(node);
        tail.store(node);
}

void QueueLockFree::produce(const Matrix& matrix){
    Node* newNode = new Node(matrix); // создаём узел
        while (true) { // пытаемся выполнить, пока не получится
            Node* curTail = tail.load(); // получаем хвост очереди
            Node* next = curTail->next.load(); // получаем следующий элемент очереди
            if (curTail == tail.load()) { // если хвост всё ещё не поменялся
                if (next == nullptr) { // если curTail всё ещё последний узел
                    if (curTail->next.compare_exchange_weak(next, newNode)) { // добавляем узел в очередь
                        tail.compare_exchange_weak(curTail, newNode); // если хвост не поменялся, то хвост теперь новый элемент 
                        return;
                    }
                } else {  // Если другой поток уже поменял хвост
                    tail.compare_exchange_weak(curTail, next); // обновляем хвост на следующий по очереди т.к. уже не актуален
                }
            }
        }
}

bool QueueLockFree::consume(Matrix& value){
    while (true) { // пока не выполнится
            Node* curHead = head.load(); // достаём голову
            Node* curTail = tail.load(); // достаём хвост
            Node* first = curHead->next.load(); // узел за головой
            if (curHead == head.load()) { // если голова всё ещё не изменилась
                if (curHead == curTail) { // если  очередь пуста
                    if (first == nullptr) {
                        // Очередь пуста
                        return false;
                    }
                    tail.compare_exchange_weak(curTail, first); // сместить  хвост на head->next
                } else { // голова и хвост указывают на разное
                    if (head.compare_exchange_weak(curHead, first)) { // head теперь head->next
                        value = curHead->data;
                        delete curHead;
                        return true;
                    }
                }
            }
        }
}
