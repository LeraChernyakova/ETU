#include "./matrix.h"
#include <algorithm>
#include <cmath>
#include <atomic>

unsigned int max_recursion = 3;

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

void strassen_calc(const Matrix a, const Matrix b, Matrix& res, int size, unsigned int recursion = 0) {
    if(size <= 128 || recursion > max_recursion) {
        res = a * b;
        return;
    }

    int half = size / 2;
    Matrix A11(half, half, false),
            A12(half, half, false),
            A21(half, half, false),
            A22(half, half, false),
            B11(half, half, false),
            B12(half, half, false),
            B21(half, half, false),
            B22(half, half, false);
    
    for (int row = 0; row < half; row++) {
        for (int col = 0; col < half; col++) {
            A11.matrix[row][col] = a.matrix[row][col];
            A12.matrix[row][col] = a.matrix[row][half + col];
            A21.matrix[row][col] = a.matrix[half + row][col];
            A22.matrix[row][col] = a.matrix[half + row][half + col];

            B11.matrix[row][col] = b.matrix[row][col];
            B12.matrix[row][col] = b.matrix[row][half + col];
            B21.matrix[row][col] = b.matrix[half + row][col];
            B22.matrix[row][col] = b.matrix[half + row][half + col];
        }
    }
            
    Matrix D(half, half, false),
            D1(half, half, false),
            D2(half, half, false),
            H1(half, half, false),
            H2(half, half, false),
            V1(half, half, false),
            V2(half, half, false);

    
    if (recursion == 0){
        vector <thread> t_calc;
        recursion++;
        t_calc.emplace_back(strassen_calc, A11 + A22, B11 + B22, ref(D), half, recursion+1);// D
        t_calc.emplace_back(strassen_calc, A12 - A22, B21 + B22, ref(D1), half, recursion+1); // D1
        t_calc.emplace_back(strassen_calc, A21 - A11, B11 + B12, ref(D2), half, recursion+1); // D2
        t_calc.emplace_back(strassen_calc, A11 + A12, B22, ref(H1), half, recursion+1); // H1 
        t_calc.emplace_back(strassen_calc, A21 + A22, B11, ref(H2), half, recursion+1); // H2
        t_calc.emplace_back(strassen_calc, A22, B21 - B11, ref(V1), half, recursion+1); // V1
        t_calc.emplace_back(strassen_calc, A11, B12 - B22, ref(V2), half, recursion+1); // V2

        for (auto &t: t_calc) t.join();
    } else {
        strassen_calc(A11 + A22, B11 + B22, D, half, recursion+1); 
        strassen_calc(A12 - A22, B21 + B22, D1, half, recursion+1);
        strassen_calc(A21 - A11, B11 + B12, D2, half, recursion+1); 
        strassen_calc(A11 + A12, B22, H1, half, recursion+1); 
        strassen_calc(A21 + A22, B11, H2, half, recursion+1); 
        strassen_calc(A22, B21 - B11, V1, half, recursion+1); 
        strassen_calc(A11, B12 - B22, V2, half, recursion+1); 
    }

    write_ci(res, move(D + D1 + V1 - H1), 0, 0, half); // c11
    write_ci(res, move(V2 + H1), 0, half, half); // c12
    write_ci(res, move(V1 + H2), half, 0, half); // c21
    write_ci(res, move(D + D2 + V2 - H2), half, half, half); // c22
}

void expand_mat(Matrix& m, int dim) {
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

Matrix prepare_mat(Matrix& a, Matrix& b) {
    int max_size = max({a.rows, a.cols, b.rows, b.cols}, [](int x, int y){ return x < y;});
    int next_pow_2 = pow(2, ceil(log2(max_size)));
    expand_mat(a, next_pow_2);
    expand_mat(b, next_pow_2);
    return Matrix(next_pow_2, next_pow_2, false);
}

Matrix strassen_alg(Matrix a, Matrix b) {
    int res_rows = a.rows, res_cols = b.cols;
    Matrix result = prepare_mat(a, b);
    strassen_calc(a, b, result, a.rows);
    for (int i = 0; i < res_rows; i++) {
        result.matrix[i].resize(res_cols);
    }
    result.matrix.resize(res_rows);
    result.rows = res_rows;
    result.cols = res_cols;      
    return result;
}