//
// Created by mikeasta on 06/12/23.
//

#pragma once

#include <string>
#include <memory>
#include "matrix.h"
#include <random>
#include <thread>
#include <iostream>

class MatrixThreading {
private:
    static void multiply_thr(Matrix &result_matrix, Matrix& matrix1, Matrix& matrix2, int iStart, int jStart, int iFinish, int jFinish) {
        int matrix_size = matrix1.get_size();

        if (iStart == iFinish) {
            for (int j = jStart; j <= jFinish; ++j) {
                int tmp = 0;
                for (int k = 0; k < matrix_size; ++k) {
                    tmp += matrix1.get_value(iStart, k) * matrix2.get_value(k, j);
                }
                result_matrix.set_value(tmp, iStart, j);
            }
        } else {
            for (int j = jStart; j < matrix_size; ++j) {
                int tmp = 0;
                for (int k = 0; k < matrix_size; ++k) {
                    tmp += matrix1.get_value(iStart, k) * matrix2.get_value(k, j);
                }
                result_matrix.set_value(tmp, iStart, j);
            }
            for (int i = iStart + 1; i < iFinish; ++i) {
                for (int j = 0; j < matrix_size; ++j) {
                    int tmp = 0;
                    for (int k = 0; k < matrix_size; ++k) {
                        tmp += matrix1.get_value(i, k) * matrix2.get_value(k, j);
                    }
                    result_matrix.set_value(tmp, i, j);
                }
            }

            for (int j = 0; j <= jFinish; ++j) {
                int tmp = 0;
                for (int k = 0; k < matrix_size; ++k) {
                    tmp += matrix1.get_value(iFinish, k) * matrix2.get_value(k, j);
                }
                result_matrix.set_value(tmp, iFinish, j);
            }
        }
    }

    static void strassen_multiply_internal(Matrix& result_matrix, Matrix& matrix1, Matrix& matrix2, bool is_first, int size_limit) {
        if (matrix1.get_size() < 2 || matrix1.get_size() < size_limit) {
            concurrent_multiply(result_matrix, 1, matrix1, matrix2);
            return;
        }

        int half = matrix1.get_size() / 2;

        Matrix A11(half);
        Matrix A12(half);
        Matrix A21(half);
        Matrix A22(half);

        Matrix B11(half);
        Matrix B12(half);
        Matrix B21(half);
        Matrix B22(half);

        for (int i = 0; i < half * 2; ++i) {
            for (int j = 0; j < half * 2; ++j) {
                if (i < half && j < half) {
                    A11.set_value(matrix1.get_value(i, j), i, j);
                    B11.set_value(matrix2.get_value(i, j), i, j);
                }
                if (i >= half && j < half) {
                    A21.set_value(matrix1.get_value(i, j), i - half, j);
                    B21.set_value(matrix2.get_value(i, j), i - half, j);
                }
                if (i < half && j >= half) {
                    A12.set_value(matrix1.get_value(i, j), i, j - half);
                    B12.set_value(matrix2.get_value(i, j), i, j - half);
                }
                if (i >= half && j >= half) {
                    A22.set_value(matrix1.get_value(i, j), i - half, j - half);
                    B22.set_value(matrix2.get_value(i, j), i - half, j - half);
                }
            }
        }

        Matrix M1(half);
        Matrix M2(half);
        Matrix M3(half);
        Matrix M4(half);
        Matrix M5(half);
        Matrix M6(half);
        Matrix M7(half);

        std::vector<std::thread> threads(6);

        Matrix temp1 = A11 + A22;
        Matrix temp2 = B11 + B22;
        Matrix temp3 = A21 + A22;
        Matrix temp4 = B12 - B22;
        Matrix temp5 = B21 - B11;
        Matrix temp6 = A11 + A12;
        Matrix temp7 = A21 - A11;
        Matrix temp8 = B11 + B12;
        Matrix temp9 = A12 - A22;
        Matrix temp10 = B21 + B22;

        if (is_first) {
            threads[0] = std::thread(strassen_multiply_internal, std::ref(M1), std::ref(temp1), std::ref(temp2), false, size_limit);
            threads[1] = std::thread(strassen_multiply_internal, std::ref(M2), std::ref(temp3), std::ref(B11), false, size_limit);
            threads[2] = std::thread(strassen_multiply_internal, std::ref(M3), std::ref(A11), std::ref(temp4), false, size_limit);
            threads[3] = std::thread(strassen_multiply_internal, std::ref(M4), std::ref(A22), std::ref(temp5), false, size_limit);
            threads[4] = std::thread(strassen_multiply_internal, std::ref(M5), std::ref(temp6), std::ref(B22), false, size_limit);
            threads[5] = std::thread(strassen_multiply_internal, std::ref(M6), std::ref(temp7), std::ref(temp8), false, size_limit);

            strassen_multiply_internal(std::ref(M7), std::ref(temp9), std::ref(temp10), false, size_limit);

            for (auto &thread : threads) {
                thread.join();
            }
        } else {
            strassen_multiply_internal(std::ref(M1), std::ref(temp1), std::ref(temp2), false, size_limit);
            strassen_multiply_internal(std::ref(M2), std::ref(temp3), std::ref(B11), false, size_limit);
            strassen_multiply_internal(std::ref(M3), std::ref(A11), std::ref(temp4), false, size_limit);
            strassen_multiply_internal(std::ref(M4), std::ref(A22), std::ref(temp5), false, size_limit);
            strassen_multiply_internal(std::ref(M5), std::ref(temp6), std::ref(B22), false, size_limit);
            strassen_multiply_internal(std::ref(M6), std::ref(temp7), std::ref(temp8), false, size_limit);
            strassen_multiply_internal(std::ref(M7), std::ref(temp9), std::ref(temp10), false, size_limit);
        }


        Matrix C11 = M1 + M4 - M5 + M7;
        Matrix C12 = M3 + M5;
        Matrix C21 = M2 + M4;
        Matrix C22 = M1 - M2 + M3 + M6;

        for (int i = 0; i < half * 2; ++i) {
            for (int j = 0; j < half * 2; ++j) {
                if (i < half && j < half) {
                    result_matrix.set_value(C11.get_value(i, j), i, j);
                }
                if (i >= half && j < half) {
                    result_matrix.set_value(C21.get_value(i - half, j), i, j);
                }
                if (i < half && j >= half) {
                    result_matrix.set_value(C12.get_value(i, j - half), i, j);
                }
                if (i >= half && j >= half) {
                    result_matrix.set_value(C22.get_value(i - half, j - half), i, j);
                }
            }
        }
    }

public:
    static void generate(Matrix& result_matrix1, Matrix& result_matrix2, int matrix_size) {
        std::random_device rd;
        std::mt19937 mt{rd()};
        std::uniform_int_distribution die100{-100, 100};

        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                result_matrix1.set_value(die100(mt), i, j);
                result_matrix2.set_value(die100(mt), i, j);
            }
        }
    }

    static void concurrent_multiply(Matrix& result_matrix, int thread_count, Matrix& matrix1, Matrix& matrix2) {
        int matrix_size = matrix1.get_size();
        int step = matrix_size * matrix_size / thread_count;

        std::vector<std::thread> threads(thread_count - 1);

        int iStart = 0;
        int jStart = 0;

        for (int i = 0; i < thread_count - 1; ++i) {
            int iFinish = iStart;
            int jFinish = jStart + step;
            if (jFinish >= matrix_size) {
                iFinish++;

                jFinish = jFinish % matrix_size;
            }

            threads[i] = std::thread(multiply_thr, std::ref(result_matrix), std::ref(matrix1), std::ref(matrix2), iStart, jStart, iFinish, jFinish);
            iStart = iFinish;
            jStart = jFinish;
        }

        multiply_thr(std::ref(result_matrix), std::ref(matrix1), std::ref(matrix2), iStart, jStart, matrix_size - 1, matrix_size - 1);

        for (auto &entry: threads) {
            entry.join();
        }
    }

    static void strassen_multiply(Matrix& result_matrix, Matrix& matrix1, Matrix& matrix2) {

        int matrix_size = matrix1.get_size();

        int nearest_power_2 = static_cast<int>(std::ceil(std::log2(matrix_size)));

        int new_size = static_cast<int>(std::pow(2, nearest_power_2));

        Matrix tmp_matrix1(new_size);
        Matrix tmp_matrix2(new_size);
        Matrix tmp_result_matrix(new_size);

        for (int i = 0; i < new_size; ++i) {
            for (int j = 0; j < new_size; ++j) {
                tmp_matrix1.set_value((i < matrix_size && j < matrix_size) ? matrix1.get_value(i, j) : 0, i, j);
                tmp_matrix2.set_value((i < matrix_size && j < matrix_size) ? matrix2.get_value(i, j) : 0, i, j);
            }
        }

        int size_limit = matrix_size / 8;

        strassen_multiply_internal(tmp_result_matrix, tmp_matrix1, tmp_matrix2, true, size_limit);

        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                result_matrix.set_value(tmp_result_matrix.get_value(i, j), i, j);
            }
        }

    }

    static void output(Matrix& matrix) {
        int matrix_size = matrix.get_size();
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                std::cout << matrix.get_value(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};
