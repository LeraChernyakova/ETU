#include <atomic>
#include <memory>
#include<utility>
#include<chrono>
#include "matrix.h"
#define WORK_TIME_MS 2000
#define MATRIX_DIM 50
#define FILENAME "result.txt"
#define CURRENT_TIME chrono::steady_clock::now()

using namespace std;

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}

chrono::time_point<std::chrono::steady_clock> start;


template<typename T>
class LockFreeQueue {
    struct Node {
        shared_ptr<T> data;
        atomic<Node*> next = nullptr;
    };

    atomic<Node*> head;
    atomic<Node*> tail;
public:
    atomic<int> inserted = 0,
                popped = 0;
    LockFreeQueue()
        : head(new Node()), tail(head.load()) {}

    void push(T val) {
        Node* new_node = new Node();
        new_node->data = make_shared<T>(move(val));
        while (true) {
            Node* last = tail.load();
            Node* next = last->next.load();
            if (last == tail.load()) {
                if (next == nullptr) {
                    if (last->next.compare_exchange_weak(next, new_node)) {
                        inserted++;
                        tail.compare_exchange_weak(last, new_node);
                        return;
                    }
                } else {
                    tail.compare_exchange_weak(last, next);
                }
            }
         
        }
    }

    bool pop(T& val) {
        while (true) {
            Node* first = head.load();
            Node* last = tail.load();
            Node* next = first->next.load();
            if (first == last) {
                if (next == nullptr) {
                    return false;
                }
                tail.compare_exchange_weak(last, next);
            } else {
                if (head.compare_exchange_weak(first, next)) {
                    popped++;
                    val = move(*next->data.get());
                    return true;
                }
            }
        }
        
    }
    
};



LockFreeQueue<pair<Matrix, Matrix>> matrices_to_mult;
LockFreeQueue<Matrix> matrices_to_print;


void consume_mtrx_to_mult() {
    pair<Matrix, Matrix> tmp(Matrix(0, 0), Matrix(0, 0));
    while (get_time_diff(start, CURRENT_TIME) < WORK_TIME_MS) {
        if (matrices_to_mult.pop(tmp)) {
            matrices_to_print.push(tmp.first * tmp.second);
        }
    }
}

void matrix_consumers_to_mult(int n) {
    vector<thread> cons;
    for (int i = 0; i < n; i++) {
        cons.emplace_back(consume_mtrx_to_mult);
    }
    for (auto &t: cons) {
        t.join();
    }    
}

void produce_matrices_to_mult() {
    while (get_time_diff(start, CURRENT_TIME) < WORK_TIME_MS) {
        matrices_to_mult.push(make_pair(Matrix(MATRIX_DIM, MATRIX_DIM), Matrix(MATRIX_DIM, MATRIX_DIM)));
    }
    
}

void matrix_producers(int n) {
    vector<thread> prods;
    for (int i = 0; i < n; i++) { 
        prods.emplace_back(produce_matrices_to_mult);
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
    int inserted = matrices_to_print.inserted;
    while (inserted > 0) {
        matrices_to_print.pop(tmp);
        out << tmp;
        inserted--;
    }
    out.close();
}



int main() {

    int producers_num, consumers_num;
    cout << "Lock-free queue.\n";
    cout << "Enter producers num and consumers num: ";
    cin >> producers_num >> consumers_num;
    start = CURRENT_TIME; 
    thread producer_thread(matrix_producers, producers_num);
    thread consumer_thread(matrix_consumers_to_mult, consumers_num);
    producer_thread.join();
    consumer_thread.join();
    thread printer_t(print_results);

    cout << "produced pairs for mult " << matrices_to_mult.inserted << '\n';
    cout << "multed pairs " << matrices_to_mult.popped << '\n';
    printer_t.join();
    return 0;
}