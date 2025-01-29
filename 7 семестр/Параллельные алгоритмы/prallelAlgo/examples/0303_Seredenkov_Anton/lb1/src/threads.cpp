#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "matrix_operations.h"

using namespace std;


void create_mat(vector<vector<int>>& first_matrix, vector<vector<int>>& second_matrix, int m, int n){
    generate_matrix(first_matrix, m, n);
    generate_matrix(second_matrix, n, m);
}

void count_mat(vector<vector<int>>& c,vector<vector<int>>& a, vector<vector<int>>& b, int m, int n){
    c = multiply_matrices(a, b, m, n);
}

int main(){
    int n = 0, m = 0;
    auto start = chrono::high_resolution_clock::now();

    cout<<"Введите размер матриц: ";
    cin>>m>>n;
    vector<vector<int>> first_matrix(m, vector<int>(n));
    vector<vector<int>> second_matrix(n, vector<int>(m));
    vector<vector<int>> result_matrix(m, vector<int>(m));

    thread make_matrix(create_mat, ref(first_matrix), ref(second_matrix), ref(m), ref(n));
    make_matrix.join();

    thread count_matrix(count_mat, ref(result_matrix), ref(first_matrix), ref(second_matrix), ref(m), ref(n));
    count_matrix.join();

    thread print_matrix(print_res, ref(result_matrix), ref(m));
    print_matrix.join();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Продолжительность работы программы: "<< duration.count()<< " ms" << endl;    
    
    return 0;
}