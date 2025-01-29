#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;


void print_res(vector<vector<int>>& matrix){
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

}

vector<vector<int>> generate_matrix(int rows, int columns){
    vector<vector<int>> matrix(rows, vector<int>(columns, 0));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}


void generate_matrices(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2){
    int n = 4096;
    matrix1 = generate_matrix(n, n);
    matrix2 = generate_matrix(n, n);
}


void thread_multiply_matrices(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, vector<vector<int>>& matrix_res, int start, int end){
    int col1 = matrix1[0].size();
    int col2 = matrix2[0].size();

    for(int i = start; i < end; i++){
        for(int j = 0; j < col2; j++){
            for(int k = 0; k < col1; k++)
                matrix_res[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
}

vector<vector<int>> lab1_mult(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int num_threads){
    vector<vector<int>> matrix_res(matrix1.size(), vector<int>(matrix2[0].size(), 0));

    vector<thread> thread_vec;
    int min_num_rows_thread = matrix1.size() / num_threads;
    int max_num_rows_thread = min_num_rows_thread + 1;
    int num_threads_with_max_rows = matrix1.size() % num_threads;

    for (int i = 0; i < num_threads; i++){
        if (i < num_threads_with_max_rows)
            thread_vec.push_back(thread(thread_multiply_matrices, ref(matrix1), ref(matrix2), ref(matrix_res),
            i * max_num_rows_thread, (i + 1) * max_num_rows_thread));
        else
            thread_vec.push_back(thread(thread_multiply_matrices, ref(matrix1), ref(matrix2), ref(matrix_res),
            num_threads_with_max_rows * max_num_rows_thread + (i - num_threads_with_max_rows) * min_num_rows_thread,
            num_threads_with_max_rows * max_num_rows_thread + (i - num_threads_with_max_rows + 1) * min_num_rows_thread));

    }

    for (int i = 0; i < thread_vec.size(); i++)
        thread_vec[i].join();

    return matrix_res;
}


void thread_scalable_mult_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, vector<vector<int>>& matrix_res, int threads_num, int threads_i){
    int r = matrix_res.size();
    int c = matrix_res[0].size();
    int N = r * c;

    for (int step = threads_i; step < N; step += threads_num) {
        int i = step / c;
        int j = step % c;
        int tmp = 0;

        for (int k = 0; k < r; k++)
            tmp += matrix1[i][k] * matrix2[k][j];

        matrix_res[i][j] = tmp;
    }

}

vector<vector<int>> scalable_mult(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int threads_num){
    vector<vector<int>> matrix_res(matrix1.size(), vector<int>(matrix2[0].size(), 0));
    vector<thread> all_threads;

    for (int i = 0; i < threads_num; i++)
        all_threads.push_back(thread(thread_scalable_mult_matrix, ref(matrix1), ref(matrix2), ref(matrix_res), threads_num, i));

    for (int i = 0; i < threads_num; i++)
        all_threads[i].join();

    return matrix_res;
}


vector<vector<int>> half_slice(vector<vector<int>>& matrix, int y, int x, int size) {
    vector<vector<int>> matrix_res(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix_res[i][j] = matrix[i + y][j + x];
        }
    }

    return matrix_res;
}


void extension_matrix(vector<vector<int>>& matrix, int dim){
    if (matrix.size() == dim && matrix[0].size() == dim)
        return;

    for(int i = 0; i < matrix.size(); i++) {
        for(int j = matrix[0].size(); j < dim; j++) {
            matrix[i].push_back(0);
        }
    }

    for (int i = matrix.size(); i < dim; i++) {
        matrix.emplace_back(dim);
    }

}


vector<vector<int>> sum_matrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2, char oper){
    vector<vector<int>> matrix_res(matrix1.size(), vector<int>(matrix1[0].size()));

    if (oper == '+'){
        for (int i = 0; i < matrix1.size(); i++){
            for (int j = 0; j < matrix1[0].size(); j++)
                matrix_res[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    else {
        for (int i = 0; i < matrix1.size(); i++){
            for (int j = 0; j < matrix1[0].size(); j++)
                matrix_res[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return matrix_res;
}


void write_res(vector<vector<int>>& res, vector<vector<int>> matrix, int y, int x, int size) {
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            res[i + y][j + x] = matrix[i][j];
        }
    }
}


void strassen_mult_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, vector<vector<int>>& matrix_res, int cur_rec_depth, int max_rec_depth){
    int size = matrix1.size();

    if (matrix1.size() <= 2 || cur_rec_depth >= max_rec_depth) {
        int row1 = matrix1.size();
        int col1 = matrix1[0].size();
        int col2 = matrix2[0].size();

        for(int i = 0; i < row1; i++){
            for(int j = 0; j < col2; j++){
                for(int k = 0; k < col1; k++)
                    matrix_res[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
        return;
    }

    int half = size / 2;
    vector<vector<int>> A11(half_slice(matrix1, 0, 0, half)),
                        A12(half_slice(matrix1, 0, half, half)),
                        A21(half_slice(matrix1, half, 0, half)),
                        A22(half_slice(matrix1, half, half, half)),
                        B11(half_slice(matrix2, 0, 0, half)),
                        B12(half_slice(matrix2, 0, half, half)),
                        B21(half_slice(matrix2, half, 0, half)),
                        B22(half_slice(matrix2, half, half, half));

    vector<vector<int>> D(half, vector<int>(half)),
                        D1(half, vector<int>(half)),
                        D2(half, vector<int>(half)),
                        H1(half, vector<int>(half)),
                        H2(half, vector<int>(half)),
                        V1(half, vector<int>(half)),
                        V2(half, vector<int>(half));

    thread t1(strassen_mult_matrix, sum_matrices(A11, A22, '+'), sum_matrices(B11, B22, '+'),  ref(D), cur_rec_depth + 1, max_rec_depth);
    thread t2(strassen_mult_matrix, sum_matrices(A12, A22, '-'), sum_matrices(B21, B22, '+'), ref(D1), cur_rec_depth + 1, max_rec_depth);
    thread t3(strassen_mult_matrix, sum_matrices(A21, A11, '-'), sum_matrices(B11, B12, '+'), ref(D2), cur_rec_depth + 1, max_rec_depth);
    thread t4(strassen_mult_matrix, sum_matrices(A11, A12, '+'),                         B22, ref(H1), cur_rec_depth + 1, max_rec_depth);
    thread t5(strassen_mult_matrix, sum_matrices(A21, A22, '+'),                         B11, ref(H2), cur_rec_depth + 1, max_rec_depth);
    thread t6(strassen_mult_matrix,                         A22, sum_matrices(B21, B11, '-'), ref(V1), cur_rec_depth + 1, max_rec_depth);
    thread t7(strassen_mult_matrix,                         A11, sum_matrices(B12, B22, '-'), ref(V2), cur_rec_depth + 1, max_rec_depth);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    vector<vector<int>> C11 = sum_matrices(sum_matrices(sum_matrices(D, D1, '+'), V1, '+'), H1, '-');
    vector<vector<int>> C12 = sum_matrices(V2, H1, '+');
    vector<vector<int>> C21 = sum_matrices(V1, H2, '+');
    vector<vector<int>> C22 = sum_matrices(sum_matrices(sum_matrices(D, D2, '+'), V2, '+'), H2, '-');
    write_res(matrix_res, std::move(C11), 0, 0, half);
    write_res(matrix_res, std::move(C12), 0, half, half);
    write_res(matrix_res, std::move(C21), half, 0, half);
    write_res(matrix_res, std::move(C22), half, half, half);
}



vector<vector<int>> strassen_mult(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int threads_num){
    int max_size = std::max({matrix1.size(), matrix1[0].size(), matrix2.size(), matrix2[0].size()});
    int dim = pow(2, ceil(log2(max_size)));

    int r = matrix1.size();
    int c = matrix2[0].size();

    extension_matrix(matrix1, dim);
    extension_matrix(matrix2, dim);

    vector<vector<int>> matrix_res(dim, vector<int>(dim, 0));

    strassen_mult_matrix(matrix1, matrix2, matrix_res, 0, 3);

    for (int i = 0; i < r; i++) {
        matrix_res[i].resize(c);
    }
    matrix_res.resize(r);

    return matrix_res;
}




bool compare_matrices(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2){
    if (matrix1.size() != matrix2.size())
        return false;

    if (matrix1[0].size() != matrix2[0].size())
        return false;

    for (int i = 0; i < matrix1.size(); i++){
        for (int j = 0; j < matrix1[0].size(); j++){
            if (matrix1[i][j] != matrix2[i][j])
                return false;
        }
    }

    return true;
}


int main()
{
    int repeat_num = 1;
    int threads_num = 20;
    unsigned long sum_scal_duration = 0;
    unsigned long sum_strassen_duration = 0;
    unsigned long sum_lab1_duration = 0;

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;

    for (int i = 0; i < repeat_num; i++){
        generate_matrices(matrix1, matrix2);

        auto start_time = chrono::high_resolution_clock::now();
        vector<vector<int>> res_scalable = scalable_mult(matrix1, matrix2, threads_num);
        auto stop_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
        sum_scal_duration += duration.count();


        start_time = chrono::high_resolution_clock::now();
        vector<vector<int>> res_lab1 = lab1_mult(matrix1, matrix2, threads_num);
        stop_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
        sum_lab1_duration += duration.count();


        start_time = chrono::high_resolution_clock::now();
        vector<vector<int>> res_strassen = strassen_mult(matrix1, matrix2, threads_num);
        stop_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
        sum_strassen_duration += duration.count();


        if (!compare_matrices(res_scalable, res_lab1))
            cout << "matrices Lab 1 and Scallable multiplication not equal!!!" << endl;

        if (!compare_matrices(res_scalable, res_strassen))
            cout << "matrices Strassen and Scallable multiplication not equal!!!" << endl;

    }

    cout << "Executing LAB 1 multiplication time:" << sum_lab1_duration / repeat_num << endl;
    cout << "Executing scalable multiplication time:" << sum_scal_duration / repeat_num << endl;
    cout << "Executing Strassen multiplication time:" << sum_strassen_duration / repeat_num << endl;
}
