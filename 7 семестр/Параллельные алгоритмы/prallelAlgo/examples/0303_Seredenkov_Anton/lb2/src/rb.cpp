#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
#include "matrix.h"
#define MATRIX_DIM 50
#define WORK_TIME_MCS 3000000
#define CURRENT_TIME chrono::steady_clock::now()


template<typename T>
class Rough_block_Queue {
private:
    mutable mutex mut;
    queue<T> data_queue;
    condition_variable con_var;
public:
    unsigned int inserted, popped;
    Rough_block_Queue() : inserted(0), popped(0) {}

    void push(T new_value) {
        lock_guard<mutex> lk(mut);
        data_queue.push(move(new_value));
        inserted++;
        con_var.notify_one(); 
    }
    
    void wait_and_pop(T& value) {
        unique_lock<mutex> lk(mut);
        con_var.wait(lk, [this] {return !data_queue.empty();});
        value = move(data_queue.front());
        popped++;
        data_queue.pop();
    }

    bool empty() const {
        lock_guard<mutex> lk(mut);
        return data_queue.empty();
    }
};

Rough_block_Queue<pair<Matrix, Matrix>> matrices_to_mult;
Rough_block_Queue<Matrix> matrices_to_print;

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::microseconds>(second - first).count();
}

void consume_matrices_to_mult(chrono::time_point<std::chrono::steady_clock>& start_time) {
    pair<Matrix, Matrix> tmp(Matrix(0, 0), Matrix(0, 0));
    while (get_time_diff(start_time, CURRENT_TIME) < WORK_TIME_MCS) {
        matrices_to_mult.wait_and_pop(tmp);
        matrices_to_print.push(tmp.first * tmp.second);  
    }    
}

void matrix_consumers(int n, chrono::time_point<std::chrono::steady_clock>& start_time) {
    vector<thread> consumers;
    for (int i = 0; i < n; i++) {
        consumers.emplace_back(consume_matrices_to_mult, ref(start_time));
    }
    for (auto &t: consumers) {
        t.join();
    }    
}

void produce_matrices_to_mult(chrono::time_point<std::chrono::steady_clock>& start_time) {
    while (get_time_diff(start_time, CURRENT_TIME) < WORK_TIME_MCS) {
        matrices_to_mult.push(make_pair(Matrix(MATRIX_DIM, MATRIX_DIM), Matrix(MATRIX_DIM, MATRIX_DIM)));
    }
    
}

void matrix_producers(int n, chrono::time_point<std::chrono::steady_clock>& start_time) {
    vector<thread> prods;
    for (int i = 0; i < n; i++) { 
        prods.emplace_back(produce_matrices_to_mult, ref(start_time));
    }
    for (auto &t: prods) { t.join(); }

}

void print_results() {
    ofstream out;
    out.open("result_1.txt");
    Matrix tmp(0, 0);
    while (!matrices_to_print.empty()) {
        matrices_to_print.wait_and_pop(tmp);
        out << tmp;
    }
    out.close();
}


int main() {
    int producers_num, consumers_num;
    cout << "Rough block\n";
    cout << "Enter producers and consumers amount: ";
    cin >> producers_num >> consumers_num;
    auto start = CURRENT_TIME; 
    thread producer_thread(matrix_producers, producers_num, ref(start));
    thread consumer_thread(matrix_consumers, consumers_num, ref(start));
    producer_thread.join();
    consumer_thread.join();
    thread printer(print_results);

    cout << "produced pairs " << matrices_to_mult.inserted << '\n';
    cout << "consumed pairs " << matrices_to_mult.popped << '\n';
    printer.join();
    return 0;
}