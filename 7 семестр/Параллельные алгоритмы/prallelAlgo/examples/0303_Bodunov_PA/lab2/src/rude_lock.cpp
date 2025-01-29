#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <thread>


using namespace std;


template<typename T>
class QueueRude {
private:
    mutable mutex mut;
    queue<T> my_queue;
    condition_variable cv;
public:
    QueueRude() {}

    void push(T new_value) {
        lock_guard<mutex> lk(mut);
        my_queue.push(std::move(new_value));
        cv.notify_one();
    }
    void wait_and_pop(T& value) {
        unique_lock<mutex> lk(mut);
        cv.wait(lk, [this] {return !my_queue.empty();});
        value = std::move(my_queue.front());
        my_queue.pop();
    }

    bool empty() {
        lock_guard<mutex> lk(mut);
        return my_queue.empty();
    }

    int size() {return my_queue.size();}
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


void generate_matrices(QueueRude<vector<vector<int>>*>& qgenerate, int calc_num, int prod_num){
    for (int i = 0; i < calc_num; i += prod_num){
        vector<vector<int>>* matrices = new vector<vector<int>>[2];

        matrices[0] = generate_matrix(30, 30);
        matrices[1] = generate_matrix(30, 30);

        qgenerate.push(matrices);
    }

}

void multiply_matrices(QueueRude<vector<vector<int>>*>& qgenerate,
                       QueueRude<vector<vector<int>>>& qmult, int calc_num, int cons_num){

    for (int i = 0; i < calc_num; i += cons_num){
        vector<vector<int>>* matrices;
        qgenerate.wait_and_pop(matrices);

        int row1 = matrices[0].size();
        int col1 = matrices[0][0].size();
        int row2 = matrices[1].size();
        int col2 = matrices[1][0].size();

        vector<vector<int>> matrix_res(matrices[0].size(), vector<int>(matrices[1][0].size(), 0));

        for(int i = 0; i < row1; i++){
            for(int j = 0; j < col2; j++){
                for(int k = 0; k < col1; k++)
                    matrix_res[i][j] += matrices[0][i][k] * matrices[1][k][j];
            }
        }

        qmult.push(matrix_res);
        delete[] matrices;
    }
}

void write_result(QueueRude<vector<vector<int>>>& qmult, int calc_num, string filename){

    for (int i = 0; i < calc_num; i++){
        vector<vector<int>> matrix_res;
        qmult.wait_and_pop(matrix_res);

        ofstream file;
        file.open(filename, ios::app);

        if (!file){
            cout << "Can't open file to write result\n";
            return;
        }

        file << "--------------------------------" << endl;

        for (int i = 0; i < matrix_res.size(); i++){
            for(int j = 0; j < matrix_res[i].size(); j++){
                file << matrix_res[i][j] << ' ';
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

    QueueRude<vector<vector<int>>*>* qgenerate = new QueueRude<vector<vector<int>>*>;
    QueueRude<vector<vector<int>>>* qmult = new QueueRude<vector<vector<int>>>;

    string out_file_name = "/home/master/work/etu/PA/lab2/result.txt";

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
