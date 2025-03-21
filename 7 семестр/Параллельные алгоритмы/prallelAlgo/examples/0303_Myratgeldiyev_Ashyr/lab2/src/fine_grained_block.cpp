#include<utility>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<chrono>
#include "matrix.h"
#define FILENAME "results2.txt"
#define WORK_TIME_MCS 3000000
#define MATRIX_DIM 50
#define CURRENT_TIME chrono::steady_clock::now()

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::microseconds>(second - first).count();
}

template<typename T>
class FGBQueue {
    struct Node {
        shared_ptr<T> data;
        unique_ptr<Node> next;
    };
    mutex head_mutex;
    unique_ptr<Node> head;
    mutex tail_mutex;
    Node* tail;
    condition_variable data_cond;
    
    Node* get_tail() {
        lock_guard<mutex> tail_lock(tail_mutex);
        return tail;
    }

    unique_lock<mutex> wait_for_data() {
        unique_lock<mutex> head_lock(head_mutex);
        data_cond.wait(head_lock,[&]{return head.get()!=get_tail();});
        return move(head_lock);
    }

    unique_ptr<Node> wait_pop_head(T& value) {
        unique_lock<mutex> head_lock(wait_for_data());
        popped++;
        value = move(*head->data);
        std::unique_ptr<Node> old_head = move(head);
        head = move(old_head->next);
        return old_head;
    }

public:
    unsigned int inserted, popped;
    FGBQueue() : head(new Node()), tail(head.get()), inserted(0), popped(0) {}

    FGBQueue(const FGBQueue& other) = delete;
    FGBQueue& operator= (const FGBQueue& other) = delete;

    void push(T new_value) {
        shared_ptr<T> new_data(make_shared<T>(move(new_value)));
        unique_ptr<Node> p(new Node());
        {
            lock_guard<mutex> tail_lock(tail_mutex);
            tail->data = new_data;
            Node* const new_tail = p.get();
            tail->next = move(p);
            tail = new_tail;
            inserted++;
        }
        data_cond.notify_one();
    }

    void wait_and_pop(T& value) {
        unique_ptr<Node> const old_head = wait_pop_head(value);
    }

    bool empty() {
        lock_guard<mutex> head_lock(head_mutex);
        return (head.get() == get_tail());
    }

};


FGBQueue<pair<Matrix, Matrix>> matrices_to_mult;
FGBQueue<Matrix> matrices_to_print;



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


int main() {
    int producers_num, consumers_num;
    cout << "Fine-grained blocking queue.\n";
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