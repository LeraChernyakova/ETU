#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
#include "matrix.h"
#define MATRIX_DIMENSION 50
#define PROCESS_DURATION_MICROSECONDS 3000000
#define CURRENT_TIME chrono::steady_clock::now()

// Шаблон класса для потокобезопасной очереди
template<typename T>
class RoughBlockQueue {
private:
    mutable mutex queue_mutex; // Мьютекс для синхронизации доступа к очереди
    queue<T> data_queue; // Стандартная очередь для хранения данных
    condition_variable data_condition; // Условная переменная для синхронизации

public:
    unsigned int items_pushed, items_popped; // Счетчики добавленных и извлеченных элементов
    RoughBlockQueue() : items_pushed(0), items_popped(0) {}

    // Добавление элемента в очередь
    void push(T new_value) {
        lock_guard<mutex> lock(queue_mutex);
        data_queue.push(move(new_value));
        items_pushed++;
        data_condition.notify_one();
    }
    
    // Извлечение элемента из очереди
    void wait_and_pop(T& value) {
        unique_lock<mutex> lock(queue_mutex);
        data_condition.wait(lock, [this] { return !data_queue.empty(); });
        value = move(data_queue.front());
        items_popped++;
        data_queue.pop();
    }

    // Проверка на пустоту очереди
    bool empty() const {
        lock_guard<mutex> lock(queue_mutex);
        return data_queue.empty();
    }
};

RoughBlockQueue<pair<Matrix, Matrix>> queue_for_multiplication; // Очередь пар матриц для умножения
RoughBlockQueue<Matrix> queue_for_printing; // Очередь результатов умножения для вывода

// Функция для вычисления разницы времени
unsigned long calculateTimeDifference(chrono::time_point<chrono::steady_clock> start, chrono::time_point<chrono::steady_clock> end) {
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

// Функция потребителя: извлекает пары матриц, умножает их и помещает результат в очередь вывода
void processMatrices(chrono::time_point<std::chrono::steady_clock>& start_time) {
    pair<Matrix, Matrix> matrix_pair(Matrix(0, 0), Matrix(0, 0));
    while (calculateTimeDifference(start_time, CURRENT_TIME) < PROCESS_DURATION_MICROSECONDS) {
        queue_for_multiplication.wait_and_pop(matrix_pair);
        queue_for_printing.push(matrix_pair.first * matrix_pair.second);  
    }    
}

// Создание и управление потоками потребителей
void createConsumers(int num_consumers, chrono::time_point<std::chrono::steady_clock>& start_time) {
    vector<thread> consumers;
    for (int i = 0; i < num_consumers; i++) {
        consumers.emplace_back(processMatrices, ref(start_time));
    }
    for (auto &t: consumers) {
        t.join();
    }    
}

// Функция производителя: генерирует пары матриц и помещает их в очередь для умножения
void generateMatrices(chrono::time_point<std::chrono::steady_clock>& start_time) {
    while (calculateTimeDifference(start_time, CURRENT_TIME) < PROCESS_DURATION_MICROSECONDS) {
        queue_for_multiplication.push(make_pair(Matrix(MATRIX_DIMENSION, MATRIX_DIMENSION), Matrix(MATRIX_DIMENSION, MATRIX_DIMENSION)));
    }
}

// Создание и управление потоками производителей
void createProducers(int num_producers, chrono::time_point<std::chrono::steady_clock>& start_time) {
    vector<thread> producers;
    for (int i = 0; i < num_producers; i++) { 
        producers.emplace_back(generateMatrices, ref(start_time));
    }
    for (auto &t: producers) { 
        t.join(); 
    }
}

// Вывод результатов умножения матриц в файл
void outputResultsToFile() {
    ofstream output_file;
    output_file.open("matrix_results.txt");
    Matrix result_matrix(0, 0);
    while (!queue_for_printing.empty()) {
        queue_for_printing.wait_and_pop(result_matrix);
        output_file << result_matrix;
    }
    output_file.close();
}

int main() {
    //ввод количества производителей и потребителей
    int num_producers, num_consumers;
    cout << "Rough Matrix Multiplication Processor\n";
    cout << "Enter number of producers and consumers: ";
    cin >> num_producers >> num_consumers;

    // Получение текущего времени для измерения длительности выполнения программы
    auto start_time = CURRENT_TIME;

    // Запуск потоков производителей и потребителей
    thread producers_thread(createProducers, num_producers, ref(start_time));
    thread consumers_thread(createConsumers, num_consumers, ref(start_time));

    // Ожидание завершения потоков производителей и потребителей
    producers_thread.join();
    consumers_thread.join();

    // Запуск потока для вывода результатов умножения матриц в файл
    thread result_thread(outputResultsToFile);

    // Вывод статистики о производстве и потреблении пар матриц
    cout << "Matrix pairs produced: " << queue_for_multiplication.items_pushed << '\n';
    cout << "Matrix pairs consumed: " << queue_for_multiplication.items_popped << '\n';

    // Ожидание завершения потока вывода результатов
    result_thread.join();
    
    return 0;
}
