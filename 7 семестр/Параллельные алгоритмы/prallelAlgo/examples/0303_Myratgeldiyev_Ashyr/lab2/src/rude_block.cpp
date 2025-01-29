#include<utility>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<chrono>
#include "matrix.h"
#define FILENAME "results1.txt"
#define MATRIX_DIM 50
#define WORK_TIME_MCS 3000000
#define CURRENT_TIME chrono::steady_clock::now()


unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second);


template<typename T>
class MyQueue {
private:
    mutable mutex mut;
    queue<T> my_queue;
    condition_variable cv;
public:
    unsigned int inserted, popped;
    MyQueue() : inserted(0), popped(0) {}

    void push(T new_value) {
        lock_guard<mutex> lk(mut);
        my_queue.push(move(new_value));
        inserted++;
        cv.notify_one(); 
    }
    void wait_and_pop(T& value) {
        unique_lock<mutex> lk(mut);
        cv.wait(lk, [this] {return !my_queue.empty();});
        value = move(my_queue.front());
        popped++;
        my_queue.pop();
    }

    bool empty() const {
        lock_guard<mutex> lk(mut);
        return my_queue.empty();
    }

    int size() {return my_queue.size();}
};


MyQueue<pair<Matrix, Matrix>> matrices_to_mult;
MyQueue<Matrix> matrices_to_print;

void consume_mtrx_to_mult(chrono::time_point<std::chrono::steady_clock>& start_time);

void matrix_consumers_to_mult(int n, chrono::time_point<std::chrono::steady_clock>& start_time);


void produce_matrices_to_mult(chrono::time_point<std::chrono::steady_clock>& start_time);

void matrix_producers(int n, chrono::time_point<std::chrono::steady_clock>& start_time);


void print_results();


int main() {

    int producers_num, consumers_num;
    cout << "Rude blocking queue.\n";
    cout << "Enter producers num and consumers num: ";
    cin >> producers_num >> consumers_num;
    auto start = CURRENT_TIME; 
    thread producer_thread(matrix_producers, producers_num, ref(start));
    thread consumer_thread(matrix_consumers_to_mult, consumers_num, ref(start));
    producer_thread.join();
    consumer_thread.join();
    thread printer_t(print_results);

    cout << "produced pairs for mult " << matrices_to_mult.inserted << '\n';
    cout << "multed pairs " << matrices_to_mult.popped << '\n';
    printer_t.join();
    return 0;
}

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::microseconds>(second - first).count();
}

void consume_mtrx_to_mult(chrono::time_point<std::chrono::steady_clock>& start_time) {
    pair<Matrix, Matrix> tmp(Matrix(0, 0), Matrix(0, 0));
    while (get_time_diff(start_time, CURRENT_TIME) < WORK_TIME_MCS) {
        matrices_to_mult.wait_and_pop(tmp);
        matrices_to_print.push(tmp.first * tmp.second);  
    }    
}

void matrix_consumers_to_mult(int n, chrono::time_point<std::chrono::steady_clock>& start_time) {
    vector<thread> cons;
    for (int i = 0; i < n; i++) {
        cons.emplace_back(consume_mtrx_to_mult, ref(start_time));
    }
    for (auto &t: cons) {
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
    out.open(FILENAME);
    if (!out.is_open()) {
        out.close();
        cout << "Error during opening the file.\n";
        return;
    }
    Matrix tmp(0, 0);
    while (!matrices_to_print.empty()) {
        matrices_to_print.wait_and_pop(tmp);
        out << tmp;
    }
    out.close();
}