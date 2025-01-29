#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
#include "matrix.h"
#define MATRIX_SIZE 50
#define OPERATION_DURATION 3000000
#define CURRENT_TIME chrono::steady_clock::now()

// Шаблон для очереди
template<typename T>
class ThinBlockQueue {
    // Структура для узла очереди
    struct QueueNode {
        shared_ptr<T> data;         // Указатель на данные в узле
        unique_ptr<QueueNode> next; // Уникальный указатель на следующий узел
    };

    mutex head_mutex;              // Мьютекс для синхронизации доступа к началу очереди
    unique_ptr<QueueNode> head;     // Уникальный указатель на начало очереди
    mutex tail_mutex;              // Мьютекс для синхронизации доступа к концу очереди
    QueueNode* tail;                // Указатель на конец очереди
    condition_variable data_cond;  // Условная переменная для синхронизации

    // Получение указателя на конец очереди
    QueueNode* getTail() {
        lock_guard<mutex> tail_lock(tail_mutex);
        return tail;
    }

    // Ожидание появления данных в очереди
    unique_lock<mutex> waitForData() {
        unique_lock<mutex> head_lock(head_mutex);
        data_cond.wait(head_lock, [&]{ return head.get() != getTail(); });
        return move(head_lock);
    }

    // Извлечение головного узла из очереди
    unique_ptr<QueueNode> popHead(T& value) {
        unique_lock<mutex> head_lock(waitForData());
        items_popped++;
        value = move(*head->data);
        unique_ptr<QueueNode> old_head = move(head);
        head = move(old_head->next);
        return old_head;
    }

public:
    unsigned int items_pushed, items_popped; // Счетчики добавленных и извлеченных элементов

    // Конструктор класса
    ThinBlockQueue() : head(new QueueNode()), tail(head.get()), items_pushed(0), items_popped(0) {}

    // Запрет конструктора копирования и оператора присваивания
    ThinBlockQueue(const ThinBlockQueue& other) = delete;
    ThinBlockQueue& operator=(const ThinBlockQueue& other) = delete;

    // Добавление элемента в очередь
    void push(T newValue) {
        shared_ptr<T> newData(make_shared<T>(move(newValue)));  // Создание shared_ptr для новых данных
        unique_ptr<QueueNode> newNode(new QueueNode());         // Создание уникального указателя на новый узел
        {
            lock_guard<mutex> tail_lock(tail_mutex);
            tail->data = newData;                   // Запись данных в узел конца очереди
            QueueNode* const newTail = newNode.get();  // Получение указателя на новый узел
            tail->next = move(newNode);              // Перемещение указателя на новый узел в конец очереди
            tail = newTail;                         // Обновление указателя на конец очереди
            items_pushed++;                         // Увеличение счетчика добавленных элементов
        }
        data_cond.notify_one();                     // Уведомление потоков о наличии новых данных
    }

    // Ожидание и извлечение элемента из очереди
    void wait_and_pop(T& value) {
        unique_ptr<QueueNode> const old_head = popHead(value);  // Извлечение головного узла
    }

    // Проверка на пустоту очереди
    bool empty() {
        lock_guard<mutex> head_lock(head_mutex);
        return (head.get() == getTail());
    }
};

// Создание объектов очередей для пар матриц и результатов умножения
ThinBlockQueue<pair<Matrix, Matrix>> queue_for_multiplication;
ThinBlockQueue<Matrix> printQueue;

// Функция для вычисления разницы времени
unsigned long calculateTimeDifference(chrono::time_point<chrono::steady_clock> start, chrono::time_point<chrono::steady_clock> end) {
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

// Функция потребителя: извлекает пары матриц, умножает их и помещает результат в очередь вывода
void processMatrices(chrono::time_point<chrono::steady_clock>& startTime) {
    pair<Matrix, Matrix> matricesPair(Matrix(0, 0), Matrix(0, 0));
    while (calculateTimeDifference(startTime, CURRENT_TIME) < OPERATION_DURATION) {
        queue_for_multiplication.wait_and_pop(matricesPair);
        printQueue.push(matricesPair.first * matricesPair.second);  
    }    
}

// Создание и управление потоками потребителей
void createConsumers(int num_consumers, chrono::time_point<chrono::steady_clock>& startTime) {
    vector<thread> consumers;
    for (int i = 0; i < num_consumers; i++) {
        consumers.emplace_back(processMatrices, ref(startTime));
    }
    for (auto &t : consumers) {
        t.join();
    }    
}

// Функция производителя: генерирует пары матриц и помещает их в очередь для умножения
void generateMatrices(chrono::time_point<chrono::steady_clock>& startTime) {
    while (calculateTimeDifference(startTime, CURRENT_TIME) < OPERATION_DURATION) {
        queue_for_multiplication.push(make_pair(Matrix(MATRIX_SIZE, MATRIX_SIZE), Matrix(MATRIX_SIZE, MATRIX_SIZE)));
    }
}

// Создание и управление потоками производителей
void createProducers(int num_producers, chrono::time_point<chrono::steady_clock>& startTime) {
    vector<thread> producers;
    for (int i = 0; i < num_producers; i++) { 
        producers.emplace_back(generateMatrices, ref(startTime));
    }
    for (auto &t : producers) { 
        t.join(); 
    }
}

// Вывод результатов умножения матриц в файл
void outputResultsToFile() {
    ofstream resultFile;
    resultFile.open("result_output.txt");
    Matrix resultMatrix(0, 0);
    while (!printQueue.empty()) {
        printQueue.wait_and_pop(resultMatrix);
        resultFile << resultMatrix;
    }
    resultFile.close();
}

int main() {
    int num_producers, num_consumers;
    cout << "Thin Matrix Multiplication Processor\n";
    cout << "Enter number of matrix producers and consumers: ";
    cin >> num_producers >> num_consumers;

    auto startTime = CURRENT_TIME; 

    // Запуск потоков производителей и потребителей
    thread producers_thread(createProducers, num_producers, ref(startTime));
    thread consumers_thread(createConsumers, num_consumers, ref(startTime));

    // Ожидание завершения потоков производителей и потребителей
    producers_thread.join();
    consumers_thread.join();

    // Запуск потока для вывода результатов умножения в файл
    thread result_thread(outputResultsToFile);

    // Вывод статистики о производстве и потреблении пар матриц
    cout << "Matrix pairs produced: " << queue_for_multiplication.items_pushed << '\n';
    cout << "Matrix pairs consumed: " << queue_for_multiplication.items_popped << '\n';

    // Ожидание завершения потока вывода результатов
    result_thread.join();

    return 0;
}
