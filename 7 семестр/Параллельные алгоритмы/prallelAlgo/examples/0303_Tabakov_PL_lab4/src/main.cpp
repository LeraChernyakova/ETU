#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include "matrix.h"
const int MATRIX_SIZE = 2048;
const int THREADS_NUM = 8;

// Функция, которую будут выполнять потоки для вычисления умножения элементов матрицы
void multiplyMatrices(Matrix& matrix1, Matrix& matrix2, Matrix& result, int start, int end) {
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                sum += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
}

void parallelMult(Matrix& matrix1, Matrix& matrix2) {
    Matrix result = Matrix(MATRIX_SIZE, true);
    std::vector<std::thread> threads;

    int step = MATRIX_SIZE / THREADS_NUM;
    int start = 0;
    int end = step;

    // Создаем и запускаем потоки для вычислений
    for (int i = 0; i < THREADS_NUM; ++i) {
        if (i == THREADS_NUM - 1) {
            // Последний поток берет оставшуюся часть
            end = MATRIX_SIZE;
        }
        threads.emplace_back(multiplyMatrices, std::ref(matrix1), std::ref(matrix2), std::ref(result), start, end);
        start = end;
        end += step;
    }

    // Дожидаемся окончания работы всех потоков
    for (auto& thread : threads) {
        thread.join();
    }
    std::ofstream file;
    file.open("pthreads.txt");
    file << result;
    file.close();
}

//Алгоритм Штрассена
void strassenMult(Matrix &result, Matrix &matrix1, Matrix &matrix2, bool is_first, int size_limit) {
    if (matrix1.matrix.size() < 2 || matrix1.matrix.size() < size_limit) {
        result = matrix1 * matrix2;
        return;
    }

    int half = matrix1.matrix.size() / 2;

    Matrix A11(half, true);
    Matrix A12(half, true);
    Matrix A21(half, true);
    Matrix A22(half, true);

    Matrix B11(half, true);
    Matrix B12(half, true);
    Matrix B21(half, true);
    Matrix B22(half, true);


    for (int i = 0; i < half * 2; ++i) {
        for (int j = 0; j < half * 2; ++j) {
            if (i < half && j < half) {
                A11.matrix[i][j] = matrix1.matrix[i][j];
                B11.matrix[i][j] = matrix2.matrix[i][j];
            }
            if (i >= half && j < half) {
                A21.matrix[i-half][j] = matrix1.matrix[i][j];
                B21.matrix[i-half][j] = matrix2.matrix[i][j];
            }
            if (i < half && j >= half) {
                A12.matrix[i][j-half] = matrix1.matrix[i][j];
                B12.matrix[i][j-half] = matrix2.matrix[i][j];
            }
            if (i >= half && j >= half) {
                A22.matrix[i-half][j-half] = matrix1.matrix[i][j];
                B22.matrix[i-half][j-half] = matrix2.matrix[i][j];
            }
        }
    }

    Matrix M1(half, true);
    Matrix M2(half, true);
    Matrix M3(half, true);
    Matrix M4(half, true);
    Matrix M5(half, true);
    Matrix M6(half, true);
    Matrix M7(half, true);

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
        threads[0] = std::thread(strassenMult, std::ref(M1), std::ref(temp1), std::ref(temp2), false, size_limit);
        threads[1] = std::thread(strassenMult, std::ref(M2), std::ref(temp3), std::ref(B11), false, size_limit);
        threads[2] = std::thread(strassenMult, std::ref(M3), std::ref(A11), std::ref(temp4), false, size_limit);
        threads[3] = std::thread(strassenMult, std::ref(M4), std::ref(A22), std::ref(temp5), false, size_limit);
        threads[4] = std::thread(strassenMult, std::ref(M5), std::ref(temp6), std::ref(B22), false, size_limit);
        threads[5] = std::thread(strassenMult, std::ref(M6), std::ref(temp7), std::ref(temp8), false, size_limit);

        strassenMult(std::ref(M7), std::ref(temp9), std::ref(temp10), false, size_limit);

        for (auto &thread : threads) {
            thread.join();
        }
    } else {
        strassenMult(std::ref(M1), std::ref(temp1), std::ref(temp2), false, size_limit);
        strassenMult(std::ref(M2), std::ref(temp3), std::ref(B11), false, size_limit);
        strassenMult(std::ref(M3), std::ref(A11), std::ref(temp4), false, size_limit);
        strassenMult(std::ref(M4), std::ref(A22), std::ref(temp5), false, size_limit);
        strassenMult(std::ref(M5), std::ref(temp6), std::ref(B22), false, size_limit);
        strassenMult(std::ref(M6), std::ref(temp7), std::ref(temp8), false, size_limit);
        strassenMult(std::ref(M7), std::ref(temp9), std::ref(temp10), false, size_limit);
    }


    Matrix C11 = M1 + M4 - M5 + M7;
    Matrix C12 = M3 + M5;
    Matrix C21 = M2 + M4;
    Matrix C22 = M1 - M2 + M3 + M6;

    for (int i = 0; i < half * 2; ++i) {
        for (int j = 0; j < half * 2; ++j) {
            if (i < half && j < half) {
                result.matrix[i][j] = C11.matrix[i][j];
            }
            if (i >= half && j < half) {
                result.matrix[i][j] = C21.matrix[i-half][j];
            }
            if (i < half && j >= half) {
result.matrix[i][j] = C12.matrix[i][j-half];
            }
            if (i >= half && j >= half) {
                result.matrix[i][j] = C22.matrix[i-half][j-half];
            }
        }
    }
}


int main() {
    Matrix matrix1 = Matrix(MATRIX_SIZE);

    std::ofstream file;
    file.open("matrix1.txt");
    file << matrix1;
    file.close();

    Matrix matrix2 = Matrix(MATRIX_SIZE);

    file.open("matrix2.txt");
    file << matrix2;
    file.close();

    auto start_time = std::chrono::high_resolution_clock::now();

    parallelMult(std::ref(matrix1), std::ref(matrix2));    

    auto end_time = std::chrono::high_resolution_clock::now();

    // Вычисление общего времени выполнения программы в миллисекундах
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Program duration " << duration << " ms" << std::endl;

    

    //STRASSEN
    Matrix strassen_result(MATRIX_SIZE, true);
    int size_limit = MATRIX_SIZE / 8;
    
    start_time = std::chrono::high_resolution_clock::now();
    
    strassenMult(std::ref(strassen_result), std::ref(matrix1), std::ref(matrix2), true, size_limit);

    end_time = std::chrono::high_resolution_clock::now();

    // Вычисление общего времени выполнения программы в миллисекундах
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Strassen Program duration " << duration << " ms" << std::endl;

    file.open("strassen.txt");
    file << strassen_result;
    file.close(); 
    return 0;
}


