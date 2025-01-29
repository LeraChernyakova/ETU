#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>


using namespace std;


template<typename T>
class QueueLockFree {
    struct Node {
        shared_ptr<T> data;
        atomic<Node*> next = nullptr;
    };

    atomic<Node*> head;
    atomic<Node*> tail;

    atomic<Node*> to_be_deleted;
    atomic<unsigned> threads_in_pop;

public:
    QueueLockFree()
        : head(new Node()), tail(head.load()) {}

    void push(T val) {
        Node* new_node = new Node();
        new_node->data = make_shared<T>(std::move(val));

        while (true) {
            Node* old_tail = tail.load();
            Node* next = old_tail->next.load();

            if (old_tail == tail.load()) {
                if (next == nullptr) {
                    if (old_tail->next.compare_exchange_weak(next, new_node)) {
                        tail.compare_exchange_weak(old_tail, new_node);
                        return;
                    }
                }
                else {
                    tail.compare_exchange_weak(old_tail, next);
                }
            }

        }
    }

    shared_ptr<T> pop() {
        while (true) {
            Node* old_head = head.load();
            Node* old_tail = tail.load();
            Node* next = old_head->next.load();

            if (old_head == head.load()) {
                if (old_head == old_tail) {
                    if (next) {
                        tail.compare_exchange_weak(old_tail,  next);
                    }
                }
                else {
                    shared_ptr<T> ret = next->data;
                    if (head.compare_exchange_weak(old_head, next)) {
                        try_reclaim(old_head);
                        return ret;
                    }
                }
            }
        }
    }

private:
    static void delete_nodes(Node* nodes) {
        while(nodes) {
            Node* next=nodes->next;
            delete nodes;
            nodes=next;
        }
    }

    void try_reclaim(Node* old_head) {
        if (threads_in_pop == 1) {
            Node* nodes_to_delete = to_be_deleted.exchange(nullptr);

            if(!--threads_in_pop)
                delete_nodes(nodes_to_delete);
            else{
                if (nodes_to_delete)
                    chain_pending_nodes(nodes_to_delete);
            }

            delete old_head;
        }
        else {
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }

    void chain_pending_nodes(Node* nodes) {
        Node* last = nodes;
        while(Node* const next=last->next) {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(Node* first, Node* last) {
        last->next = to_be_deleted.load();
        Node* next = last->next.load();
        while(!to_be_deleted.compare_exchange_weak(next, first));
    }

    void chain_pending_node(Node* n) {
        chain_pending_nodes(n, n);
    }
};




vector<vector<int>> generate_matrix(int rows, int columns){
    vector<vector<int>> matrix(rows, vector<int>(columns, 0));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}


void generate_matrices(QueueLockFree<vector<vector<int>>*>& qgenerate, int calc_num, int prod_num){
    for (int i = 0; i < calc_num; i += prod_num){
        vector<vector<int>>* matrices = new vector<vector<int>>[2];

        matrices[0] = generate_matrix(30, 30);
        matrices[1] = generate_matrix(30, 30);

        qgenerate.push(matrices);
    }

}

void multiply_matrices(QueueLockFree<vector<vector<int>>*>& qgenerate,
                       QueueLockFree<vector<vector<int>>>& qmult, int calc_num, int cons_num){

    for (int i = 0; i < calc_num; i += cons_num){
        std::shared_ptr<vector<vector<int>>*> matrices = qgenerate.pop();

        int row1 = (*matrices)[0].size();
        int col1 = (*matrices)[0][0].size();
        int row2 = (*matrices)[1].size();
        int col2 = (*matrices)[1][0].size();

        vector<vector<int>> matrix_res((*matrices)[0].size(), vector<int>((*matrices)[1][0].size(), 0));

        for(int i = 0; i < row1; i++){
            for(int j = 0; j < col2; j++){
                for(int k = 0; k < col1; k++)
                    matrix_res[i][j] += (*matrices)[0][i][k] * (*matrices)[1][k][j];
            }
        }

        qmult.push(matrix_res);
        delete[] (*matrices);
    }
}

void write_result(QueueLockFree<vector<vector<int>>>& qmult, int calc_num, string filename){

    for (int i = 0; i < calc_num; i++){
        shared_ptr<vector<vector<int>>> matrix_res = qmult.pop();

        ofstream file;
        file.open(filename, ios::app);

        if (!file){
            cout << "Can't open file to write result\n";
            return;
        }

        file << "--------------------------------" << endl;

        for (int i = 0; i < matrix_res->size(); i++){
            for(int j = 0; j < (*matrix_res)[i].size(); j++){
                file << (*matrix_res)[i][j] << ' ';
            }
            file << endl;
        }

        file.close();
    }
}


int main()
{
    int calc_num = 300;
    int repeat_num = 100;
    int prod_num = 100;
    int cons_num = 100;
    unsigned long sum_duration = 0;

    QueueLockFree<vector<vector<int>>*>* qgenerate = new QueueLockFree<vector<vector<int>>*>;
    QueueLockFree<vector<vector<int>>>* qmult = new QueueLockFree<vector<vector<int>>>;

    string out_file_name = "/home/master/work/etu/PA/lab3/result.txt";

    for (int i = 0; i < repeat_num; i++){
        remove(out_file_name.c_str());

        auto start_time = chrono::high_resolution_clock::now();

        vector<thread> all_threads;

        for (int j = 0; j < prod_num; j++)
            all_threads.push_back(thread(generate_matrices, ref(*qgenerate), calc_num, prod_num));

        for (int j = 0; j < cons_num; j++)
            all_threads.push_back(thread(multiply_matrices, ref(*qgenerate), ref(*qmult), calc_num, cons_num));

        all_threads.push_back(thread(write_result, ref(*qmult), calc_num, out_file_name));

        for (int j = 0; j < prod_num + cons_num + 1; j++) {
            all_threads[j].join();
        }

        auto stop_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);

        sum_duration += duration.count();
    }

    cout << "Executing time:" << sum_duration / repeat_num << endl;

    delete qgenerate;
    delete qmult;
}
