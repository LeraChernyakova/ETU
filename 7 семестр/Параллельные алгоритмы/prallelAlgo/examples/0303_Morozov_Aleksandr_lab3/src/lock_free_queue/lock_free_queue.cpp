#include <atomic>


template<typename T>
class LockFreeQueue {
private:

    struct Node {
        Node() {
            next = nullptr;
        }

        Node(T element) {
            value = element;
            next = nullptr;
        };

        T value;
        std::atomic<Node*> next;
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue() {
        // Заглушка для избежания пустоты очереди
        Node* dummy = new Node();
        head.store(dummy);
        tail.store(dummy);
    }

    void add(T element_value) {
        // Создаем элемент с новыми данными
        Node* new_element = new Node(element_value);
        while (true) {
            // Сохраняем хвост 
            Node* curr_tail = tail.load();
            Node* next_nullptr = nullptr;
            // * Если хвост является последним элементом, пытаемся записать новый узел
            if ((curr_tail->next).compare_exchange_weak(next_nullptr, new_element)) {
                // * Если получилось записать, то
                // Пытаемся передвинуть указатель хвоста на записанный элемент
                tail.compare_exchange_weak(curr_tail, new_element);
                // Если получилось, то текущий поток сдвинул указатель
                // Если нет, то это сделал другой поток
                break;
            } else {
                // * Если не получилось записать, то
                // Текущий указатель хвоста - не последний в очереди
                // Двигаем его дальше
                // Если получилось, то текущий поток сдвинул указатель
                // Если нет, то это сделал другой поток
                tail.compare_exchange_weak(curr_tail, curr_tail->next.load());
            }
        }
    }

    bool get(T &element_value) {
        while (true) {
            // Сохраняем голову
            Node* curr_head = head.load();
            // Сохраняем хвост 
            Node* curr_tail = tail.load();
            // Сохраняем следующий за головой узел
            Node* next_head = (curr_head->next).load();

            // * Возможно очередь пуста
            if (curr_head == curr_tail) {
                // Следующего элемента нет, очередь точно пуста
                if (!next_head) return false;
                // Следующий элемент есть, значит хвост не успел подвинуться после добавления
                else {
                    // Помогаем ему подвинуться 
                    tail.compare_exchange_weak(curr_tail, next_head);
                }
            // * Очередь точно не пуста
            } else {
                // Если голова не поменялась, то переставляем ее на следующий элемент
                if (head.compare_exchange_weak(curr_head, next_head)) {
                    // Забираем значение
                    element_value = next_head->value;
                    return true;
                }
            }
        }
    }
};