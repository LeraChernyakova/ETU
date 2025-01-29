#include "./matrix.h"
#include <utility>
#include <chrono>
#include <algorithm>
#include <cmath>
#define CURRENT_TIME chrono::steady_clock::now()

int INIT_SIZE;

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}


using namespace std;


bool is_power_of_2(int n) {
    return n > 0 && ((n & (n - 1)) == 0);
}

class MatrixMultiplier {
    
    void parallel_mult_helper(const Matrix& a, const Matrix& b, Matrix& res, int thread_count, int thread_idx) {
        int newRows = res.rows, newCols = res.cols;
        int i, j, tmp;
        for (int step = thread_idx; step < newRows * newCols; step += thread_count) {
            i = step / newCols;
            j = step % newCols;
            tmp = 0;
            for (int k = 0; k < newRows; k++) {
                tmp += (a.matrix[i][k] * b.matrix[k][j]);
            }
            res.matrix[i][j] = tmp;
        }
    }
    
    Matrix get_square_slice(const Matrix& m, int i, int j, int size) {
        Matrix tmp(size, size, false);
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                tmp.matrix[y][x] = m.matrix[i+y][j+x];
            }
        }
        return tmp;
    }

    void write_ci(Matrix& res, const Matrix& ci, int y, int x, int size) {
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                res.matrix[i + y][j + x] = ci.matrix[i][j];
            }
        }
    }

    void strassen_helper(const Matrix a, const Matrix b, Matrix& res, int size) {
        if(size <= INIT_SIZE / 8) {
            res = a * b;
            return;
        }
        int half = size / 2;
        Matrix A11(get_square_slice(a, 0, 0, half)),
               A12(get_square_slice(a, 0, half, half)),
               A21(get_square_slice(a, half, 0, half)),
               A22(get_square_slice(a, half, half, half)),
               B11(get_square_slice(b, 0, 0, half)),
               B12(get_square_slice(b, 0, half, half)),
               B21(get_square_slice(b, half, 0, half)),
               B22(get_square_slice(b, half, half, half));
               
        Matrix D(half, half, false),
              D1(half, half, false),
              D2(half, half, false),
              H1(half, half, false),
              H2(half, half, false),
              V1(half, half, false),
              V2(half, half, false);

        thread t1(&MatrixMultiplier::strassen_helper, this, A11 + A22, B11 + B22, ref(D), half);  //  D
        thread t2(&MatrixMultiplier::strassen_helper, this, A12 - A22, B21 + B22, ref(D1), half); // D1
        thread t3(&MatrixMultiplier::strassen_helper, this, A21 - A11, B11 + B12, ref(D2), half); // D2
        thread t4(&MatrixMultiplier::strassen_helper, this, A11 + A12, B22,       ref(H1), half);       // H1 
        thread t5(&MatrixMultiplier::strassen_helper, this, A21 + A22, B11,       ref(H2), half);       // H2    
        thread t6(&MatrixMultiplier::strassen_helper, this, A22,       B21 - B11, ref(V1), half);       // V1   
        thread t7(&MatrixMultiplier::strassen_helper, this, A11,       B12 - B22, ref(V2), half);       // V2   
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();


        write_ci(res, move(D + D1 + V1 - H1), 0, 0, half); // c11
        write_ci(res, move(V2 + H1), 0, half, half); // c12
        write_ci(res, move(V1 + H2), half, 0, half); // c21
        write_ci(res, move(D + D2 + V2 - H2), half, half, half); // c22
    }

    void expand_matrix(Matrix& m, int dim) {
        for(int i = 0; i < m.rows; i++) {
            for(int j = m.cols; j < dim; j++) {
                m.matrix[i].push_back(0);
            }
        }
        for (int i = m.rows; i < dim; i++) {
            m.matrix.emplace_back(dim);
        }
        m.cols = m.rows = dim;
    }

    Matrix prepare_matrices(Matrix& a, Matrix& b) {
        int max_size = max({a.rows, a.cols, b.rows, b.cols}, [](int x, int y){ return x < y;});
        int next_pow_2 = pow(2, ceil(log2(max_size)));
        expand_matrix(a, next_pow_2);
        expand_matrix(b, next_pow_2);
        return Matrix(next_pow_2, next_pow_2, false);
    }

    public:
    MatrixMultiplier() = default;

    Matrix no_parallel(const Matrix& a, const Matrix& b) {
        if (a.cols != b.rows) {
            return Matrix(0, 0, false);
        }
        Matrix result(a.rows, b.cols, false);
        int tmp = 0;
        for(int i = 0; i < a.rows; i++) {
            for(int j = 0; j < b.cols; j++) {
                tmp = 0;
                for (int k = 0; k < b.rows; k++) {
                    tmp += (a.matrix[i][k] * b.matrix[k][j]);
                }
                result.matrix[i][j] = tmp;
            }
        }
        return result;
    }
    
    Matrix parallel(const Matrix& a, const Matrix& b, int thread_count) {
        if (a.cols != b.rows) {
            return Matrix(0, 0, false);
        }
        vector<thread> my_threads;
        Matrix result(a.rows, b.cols, false);

        for (int i = 0; i < thread_count; i++) {
            my_threads.emplace_back(&MatrixMultiplier::parallel_mult_helper, this, ref(a), ref(b), ref(result), thread_count, i);
        }
        for (auto &t: my_threads) {
           t.join();
        }
        return result;
    }

    Matrix strassen_alg(Matrix a, Matrix b) {
        if(a.cols != b.rows) { 
            cout << "Error while multiplying matrices with Strassen's algorithm: wrong dimensions\n";
            return Matrix(0, 0, false);
        }
        int res_rows = a.rows, res_cols = b.cols;
        Matrix result = prepare_matrices(a, b);
        INIT_SIZE = a.rows;
        strassen_helper(a, b, result, a.rows);
        for (int i = 0; i < res_rows; i++) {
            result.matrix[i].resize(res_cols);
        }
        result.matrix.resize(res_rows);
        result.rows = res_rows;
        result.cols = res_cols;      
        return result;
    }

};

int main() {
    std::cout << "Compare matrix multiplication algorithms.\n";
    int thread_count = 3;
    MatrixMultiplier matrix_multer;
    int tests[] = {64, 128, 256, 512, 1024, 2048, 4096};
    int tests_count = sizeof(tests)/sizeof(int);
    int dim;
    chrono::time_point<std::chrono::steady_clock> start;
    Matrix cur_res;
    for (int i = 0; i < tests_count; i++) {
        cout << "Test #" << i+1 << ": matrix " << tests[i] << 'x' << tests[i] << '\n';
        dim = tests[i];
        Matrix a(dim, dim, true), b(dim, dim, true);
        
        start = CURRENT_TIME;
        cur_res = matrix_multer.strassen_alg(a, b);
        cout << "Strassen: " << get_time_diff(start, CURRENT_TIME) << "ms\n";
        
        start = CURRENT_TIME;
        cur_res = matrix_multer.parallel(a, b, thread_count);
        cout << "Multithread: " << get_time_diff(start, CURRENT_TIME) << "ms\n";
    }



    return 0;
}