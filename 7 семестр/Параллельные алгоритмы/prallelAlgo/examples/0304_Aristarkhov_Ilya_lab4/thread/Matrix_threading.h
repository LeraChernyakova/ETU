#ifndef PA_LAB_2_MATRIX_THREADING_H
#define PA_LAB_2_MATRIX_THREADING_H

#include <string>
#include <memory>
#include <thread>
#include "../model/Square_matrix.h"

class Matrix_threading {
private:
    static void multiply_thr(Square_matrix &result_matrix, Square_matrix& matrix1, Square_matrix& matrix2, int iStart, int jStart, int iFinish, int jFinish);
    static void strassen_multiply_internal(Square_matrix& result_matrix, Square_matrix& matrix1, Square_matrix& matrix2, bool is_first, int size_limit);
public:
    static void generate(Square_matrix& result_matrix1, Square_matrix& result_matrix2, int matrix_size);
    static void concurrent_multiply(Square_matrix& result_matrix, int thread_count, Square_matrix& matrix1, Square_matrix& matrix2);
    static void strassen_multiply(Square_matrix& result_matrix, Square_matrix& matrix1, Square_matrix& matrix2);
    static void output(std::string_view path, Square_matrix& matrix);
};


#endif //PA_LAB_2_MATRIX_THREADING_H
