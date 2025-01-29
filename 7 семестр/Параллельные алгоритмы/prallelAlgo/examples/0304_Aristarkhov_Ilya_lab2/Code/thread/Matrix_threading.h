#ifndef PA_LAB_2_MATRIX_THREADING_H
#define PA_LAB_2_MATRIX_THREADING_H

#include <string>
#include "../model/Square_matrix.h"
#include "../model/queue/Thread_safe_queue.h"

class Matrix_threading {
private:
    static void multiply_thr(Square_matrix &result_matrix, std::shared_ptr<std::pair<Square_matrix, Square_matrix>> matrices, int iStart, int jStart, int iFinish, int jFinish);
public:
    static void generate(int matrix_size, std::shared_ptr<Thread_safe_queue<std::pair<Square_matrix, Square_matrix>>> save_queue);
    static void multiply(int thread_count, std::shared_ptr<Thread_safe_queue<Square_matrix>> save_queue, std::shared_ptr<std::pair<Square_matrix, Square_matrix>> matrices);
    static void output(std::string_view path, std::shared_ptr<Square_matrix> matrix);
};


#endif //PA_LAB_2_MATRIX_THREADING_H
