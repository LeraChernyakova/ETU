#include <iostream>
#include <thread>
#include <vector>

#include "matrix_operations.h"

int n = 0, m = 0;

void multiply(int start, int end, const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void create_mat(vector<vector<int>>& first_matrix, vector<vector<int>>& second_matrix, int m, int n){
    generate_matrix(first_matrix, m, n);
    generate_matrix(second_matrix, n, m);
}

int main() {
    cout<<"Введите размер матриц: ";
    cin>>m>>n;

    int THREADS = 0;
    cout<<"Введите количество потоков: ";
    cin>>THREADS;
    vector<vector<int>> first_matrix(m, vector<int>(n));
    vector<vector<int>> second_matrix(n, vector<int>(m));
    vector<vector<int>> result_matrix(m, vector<int>(m));

    auto start = chrono::high_resolution_clock::now();
    thread make_matrix(create_mat, ref(first_matrix), ref(second_matrix), ref(m), ref(n));
    make_matrix.join();

    std::vector<std::thread> threads;
    int chunk_size = m / THREADS;
    for (int i = 0; i < THREADS; i++) {
        int start = i * chunk_size;
        int end = (i == THREADS - 1) ? m : (i + 1) * chunk_size;
        threads.emplace_back(multiply, start, end, std::ref(first_matrix), std::ref(second_matrix), std::ref(result_matrix));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    print_res(result_matrix, m);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Продолжительность работы программы: "<< duration.count()<< " ms" << endl;

    return 0;
} 