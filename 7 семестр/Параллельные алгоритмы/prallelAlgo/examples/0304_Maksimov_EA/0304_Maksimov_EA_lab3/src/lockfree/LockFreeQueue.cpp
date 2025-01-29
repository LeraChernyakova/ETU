#include "LockFreeQueue.h"

Node::Node() {
    this->data = generateMatrix();
    this->next = nullptr;
}

Node::~Node() {}

LockFreeQueue::LockFreeQueue() {
    Node* newNode = new Node;
    this->nodeHead.store(newNode);  // store - сохранить в atomic
    this->nodeTail.store(newNode);  // store - сохранить в atomic
}

LockFreeQueue::~LockFreeQueue() {}

void LockFreeQueue::push() {
    #ifdef DEBUG
        std::cout << "Add started ";
    #endif

    Node* pushNode = new Node;
    while(true) {                                                       // До тех пор, пока не получится.
        Node* currentTailNode = this->nodeTail.load();                  // load - взять из atomic
        Node* nextAfterCurrentTailNode = currentTailNode->next.load();  // load - взять из atomic
        if (currentTailNode != this->nodeTail.load()) {                 // Если текущий хвост НЕ успел обновиться (load - взять из atomic),
            continue;                                                   // то попробовать позже.
        }

        if (nextAfterCurrentTailNode == nullptr) {                                                  // Если это действительно хвост
            if (currentTailNode->next.compare_exchange_weak(nextAfterCurrentTailNode, pushNode)) {  // то добавляем новый элемент в конец. 2. Получаем результат сравнения, если добавили новое,
                this->nodeTail.compare_exchange_weak(currentTailNode, pushNode);                    // то меняем хвост очереди.
                #ifdef DEBUG
                    std::cout << "Add finished" << std::endl;
                #endif
                return;
            }
        } else {                                                                                    // Иначе это не хвост!
            this->nodeTail.compare_exchange_weak(currentTailNode, nextAfterCurrentTailNode);        // Помогаем обновить хвост очереди.
        }
    }
}

bool LockFreeQueue::pop(Matrix& returnMatrix) {
    #ifdef DEBUG
        std::cout << "Delete started ";
    #endif
    
    while (true) {
        Node* currentHeadNode = this->nodeHead.load();                  // load - взять из atomic
        Node* currentTailNode = this->nodeTail.load();                  // load - взять из atomic
        Node* nextAfterCurrentHeadNode = currentHeadNode->next.load();  // load - взять из atomic

        if (currentHeadNode != this->nodeHead.load()) {                 // Если текущая голова успела обновиться (load - взять из atomic),
            continue;                                                   // то с ней кто-то работает, попробовать позже.
        }

        if (currentHeadNode == currentTailNode) {                       // Если голова и хвост равны, то
            if (nextAfterCurrentHeadNode == nullptr) {                  // проверить, не добавляется ли что-то после головы. Если ничего нет,
                #ifdef DEBUG                                            // то действительно 1 элемент,
                    std::cout << "Delete failed" << std::endl;
                #endif
                return false;                                           // удаление не получилось.
            }                                                                                   // Иначе что-то добавляется.
            this->nodeTail.compare_exchange_weak(currentTailNode, nextAfterCurrentHeadNode);    // Помогаем обновить хвост очереди.
            continue;                                                                           // Попробовать позже.
        } 
        
        if (this->nodeHead.compare_exchange_weak(currentHeadNode, nextAfterCurrentHeadNode)) {   // Голова и хвост НЕ равны, очередь не пустая. Пытаемся обновить текущую голову на следующий элемент. Если успешно обновляется,
            returnMatrix = currentHeadNode->data;                                                // то удаление успешно.
            delete currentHeadNode;                         
            #ifdef DEBUG
                std::cout << "Delete finished" << std::endl;
            #endif
            return true;
        }
    }
}
