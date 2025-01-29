#include "Matrix_threading.h"
#include <random>
#include <thread>
#include <fstream>


void
Matrix_threading::generate(int matrix_size, std::shared_ptr<Thread_safe_queue<std::pair<Square_matrix, Square_matrix>>> save_queue) {
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution die100{-100, 100};

    std::pair<Square_matrix, Square_matrix> matrices = std::make_pair(Square_matrix(matrix_size),
                                                                      Square_matrix(matrix_size));

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            matrices.first.set_data(die100(mt), i, j);
            matrices.second.set_data(die100(mt), i, j);
        }
    }

    save_queue->push(matrices);
}

void
Matrix_threading::multiply_thr(Square_matrix &result_matrix, std::shared_ptr<std::pair<Square_matrix, Square_matrix>> matrices,
                               int iStart, int jStart, int iFinish,
                               int jFinish) {
    int matrix_size = matrices->first.get_size();

    if (iStart == iFinish) {
        for (int j = jStart; j <= jFinish; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrix_size; ++k) {
                tmp += matrices->first.get_data(iStart, k) * matrices->second.get_data(k, j);
            }
            result_matrix.set_data(tmp, iStart, j);
        }
    } else {
        for (int j = jStart; j < matrix_size; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrix_size; ++k) {
                tmp += matrices->first.get_data(iStart, k) * matrices->second.get_data(k, j);
            }
            result_matrix.set_data(tmp, iStart, j);
        }
        for (int i = iStart + 1; i < iFinish; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                int tmp = 0;
                for (int k = 0; k < matrix_size; ++k) {
                    tmp += matrices->first.get_data(i, k) * matrices->second.get_data(k, j);
                }
                result_matrix.set_data(tmp, i, j);
            }
        }

        for (int j = 0; j <= jFinish; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrix_size; ++k) {
                tmp += matrices->first.get_data(iFinish, k) * matrices->second.get_data(k, j);
            }
            result_matrix.set_data(tmp, iFinish, j);
        }
    }
}

void Matrix_threading::multiply(int thread_count, std::shared_ptr<Thread_safe_queue<Square_matrix>> save_queue,
                                std::shared_ptr<std::pair<Square_matrix, Square_matrix>> matrices) {
    int matrix_size = matrices->first.get_size();

    Square_matrix result_matrix(matrix_size);


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

        threads[i] = std::thread(multiply_thr, std::ref(result_matrix), matrices, iStart, jStart, iFinish,
                                 jFinish);

        iStart = iFinish;
        jStart = jFinish;
    }

    multiply_thr(std::ref(result_matrix), matrices, iStart, jStart, matrix_size - 1, matrix_size - 1);

    for (auto &entry: threads) {
        entry.join();
    }

    save_queue->push(result_matrix);
}

void Matrix_threading::output(std::string_view path, std::shared_ptr<Square_matrix> matrix) {
    std::ofstream outf{static_cast<std::string>(path)};

    if (!outf) {
        printf("Couldn't open output file for writing.\n");
    }
    int matrix_size = matrix->get_size();

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            outf << matrix->get_data(i, j) << " ";
        }
        outf << "\n";
    }

    outf.close();
}


