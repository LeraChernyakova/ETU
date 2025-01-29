#include <atomic>
#include <memory>
#include <chrono>
#include "matrix.h" 
#define WORK_TIME_MS 3000 // Определение времени работы в миллисекундах.
#define MATRIX_DIM 50 // Определение размерности матриц.
#define CURRENT_TIME chrono::steady_clock::now() 

using namespace std;

// Шаблонный класс для безблокирующей очереди.
template<typename T>
class LockFree {
    // Структура узла для очереди.
    struct Node {
        T data;
        atomic<Node*> next = nullptr;
    };

    atomic<Node*> head; // Атомарный указатель на начало очереди.
    atomic<Node*> tail; // Атомарный указатель на конец очереди.

public:
    atomic<int> items_pushed, items_popped; // Атомарные счетчики добавленных и извлеченных элементов из очереди.
    
    // Конструктор инициализирует head и tail новым узлом
    LockFree(): head(new Node()), tail(head.load()), items_pushed(0), items_popped(0) {}

    // Функция для добавления значения в очередь.
    void push(T val) {
        Node* new_node = new Node(); // Создание нового узла.
        new_node->data = move(val); // Перемещение значения в узел.
        while (true) {
            Node* last = tail.load(); // Загрузка текущего конца.
            Node* next = last->next.load(); // Загрузка указателя на следующий узел.
            if (last == tail.load()) {
                if (next == nullptr) {
                    if (last->next.compare_exchange_weak(next, new_node)) {
                        items_pushed++;
                        tail.compare_exchange_weak(last, new_node); // Обновление конца.
                        return;
                    }
                } else {
                    tail.compare_exchange_weak(last, next);
                }
            }
        }
    }

    // Функция для извлечения значения из очереди.
    bool pop(T& val) {
        while (true) {
            Node* first = head.load(); // Загрузка текущего начала.
            Node* last = tail.load(); // Загрузка текущего конца.
            Node* second = first->next.load(); // Загрузка указателя на следующий узел начала.
            if (first == last) {
                if (second == nullptr) {
                    return false; // Очередь пуста.
                }
                tail.compare_exchange_weak(last, second); // Обновление конца.
            } else {
                if (head.compare_exchange_weak(first, second)) {
                    items_popped++; 
                    val = move(first->data); // Перемещение значения из узла в выходной параметр.
                    return true;
                }
            }
        } 
    }
    
    // Деструктор для очистки памяти от оставшихся узлов в очереди.
    ~LockFree() {
        Node* cur = head.load();
        Node* tmp;
        while (cur) {
            tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
};

chrono::time_point<std::chrono::steady_clock> start;

LockFree<pair<Matrix, Matrix>> queue_for_multiplication;
LockFree<Matrix> matrices_to_print;

// Функция для вычисления разницы во времени в миллисекундах между двумя временными точками.
unsigned long calculateTimeDifference(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}

// Функция для обработки матриц путем их умножения и добавления результата в очередь.
void processMatrices() {
    pair<Matrix, Matrix> tmp(Matrix(0, 0), Matrix(0, 0));
    while (calculateTimeDifference(start, CURRENT_TIME) < WORK_TIME_MS) {
        if (queue_for_multiplication.pop(tmp)) {
            matrices_to_print.push(tmp.first * tmp.second);
        }
    }
}

// Функция для создания указанного числа потоков-потребителей для обработки матриц.
void createConsumers(int n) {
    vector<thread> cons;
    for (int i = 0; i < n; i++) {
        cons.emplace_back(processMatrices);
    }
    for (auto &t: cons) {
        t.join();
    }    
}

// Функция для генерации матриц и добавления их в очередь в течение указанного времени.
void generateMatrices() {
    while (calculateTimeDifference(start, CURRENT_TIME) < WORK_TIME_MS) {
        queue_for_multiplication.push(make_pair(Matrix(MATRIX_DIM, MATRIX_DIM), Matrix(MATRIX_DIM, MATRIX_DIM)));
    }
}

// Функция для создания указанного числа потоков-производителей для генерации матриц.
void createProducers(int n) {
    vector<thread> prods;
    for (int i = 0; i < n; i++) { 
        prods.emplace_back(generateMatrices);
    }
    for (auto &t: prods) { 
        t.join(); 
    }
}

// Вывод результатов умножения матриц в файл
void outputResultsToFile() {
    ofstream out;
    out.open("result.txt");
    Matrix tmp(0, 0);
    int i = matrices_to_print.items_pushed;
    while (i > 0) {
        matrices_to_print.pop(tmp);
        out << tmp;
        i--;
    }
    out.close();
}

int main() {
    int num_producers, num_consumers;
    cout << "Lock free\n";
    cout << "Enter number of producers and consumers: ";
    cin >> num_producers >> num_consumers;
    start = CURRENT_TIME; 

    thread producer_thread(createProducers, num_producers);
    thread consumer_thread(createConsumers, num_consumers);
    producer_thread.join();
    consumer_thread.join();
    thread result_thread(outputResultsToFile);

    cout << "Matrix pairs produced: " << queue_for_multiplication.items_pushed << '\n';
    cout << "Matrix pairs consumed: " << queue_for_multiplication.items_popped << '\n';
    result_thread.join();
    return 0;
}
