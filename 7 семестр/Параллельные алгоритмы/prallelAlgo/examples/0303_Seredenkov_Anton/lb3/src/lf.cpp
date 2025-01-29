#include <atomic>
#include <memory>
#include <chrono>
#include "matrix.h"
#define WORK_TIME_MS 3000
#define MATRIX_DIM 50
#define CURRENT_TIME chrono::steady_clock::now()

using namespace std;


template<typename T>
class LockFree {
    struct Node {
        T data;
        atomic<Node*> next = nullptr;
    };

    atomic<Node*> head;
    atomic<Node*> tail;

public:
    atomic<int> inserted, popped;
    LockFree(): head(new Node()), tail(head.load()), inserted(0), popped(0) {}

    void push(T val) {
        Node* new_node = new Node();
        new_node->data = move(val);
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
            Node* second = first->next.load();
            if (first == last) {
                if (second == nullptr) {
                    return false;
                }
                tail.compare_exchange_weak(last, second);
            } else {
                if (head.compare_exchange_weak(first, second)) {
                    popped++;
                    val = move(first->data);
                    delete first;
                    return true;
                }
            }
        } 
    }
    
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

LockFree<pair<Matrix, Matrix>> matrices_to_mult;
LockFree<Matrix> matrices_to_print;

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}

void consume_mtrx_to_mult() {
    pair<Matrix, Matrix> tmp(Matrix(0, 0), Matrix(0, 0));
    while (get_time_diff(start, CURRENT_TIME) < WORK_TIME_MS) {
        if (matrices_to_mult.pop(tmp)) {
            matrices_to_print.push(tmp.first * tmp.second);
        }
    }
}

void matrix_consumers(int n) {
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
    out.open("result.txt");
    Matrix tmp(0, 0);
    int i = matrices_to_print.inserted;
    while (i > 0) {
        matrices_to_print.pop(tmp);
        out << tmp;
        i--;
    }
    out.close();
}



int main() {
    int producers_num, consumers_num;
    cout << "Lock free\n";
    cout << "Enter producers and consumers amount: ";
    cin >> producers_num >> consumers_num;
    start = CURRENT_TIME; 
    thread producer_thread(matrix_producers, producers_num);
    thread consumer_thread(matrix_consumers, consumers_num);
    producer_thread.join();
    consumer_thread.join();
    thread printer(print_results);

    cout << "produced pairs " << matrices_to_mult.inserted << '\n';
    cout << "consumed pairs " << matrices_to_mult.popped << '\n';
    printer.join();
    return 0;
}