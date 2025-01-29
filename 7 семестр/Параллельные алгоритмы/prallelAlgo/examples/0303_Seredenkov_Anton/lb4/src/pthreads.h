#include "strassen.h"
#include <thread>

using namespace std;

void multiplier(const Matrix& a, const Matrix& b, Matrix& res, int thread_amount, int thread_idx) {
        int newRows = res.rows, newCols = res.cols;
        for (int step = thread_idx; step < newRows * newCols; step += thread_amount) {
            int i = step / newCols;
            int j = step % newCols;
            res.matrix[i][j] = 0;
            for (int k = 0; k < newRows; k++) {
                res.matrix[i][j] += (a.matrix[i][k] * b.matrix[k][j]);
            }
        }
    }

Matrix parallel(const Matrix& a, const Matrix& b, int thread_amount) {
    vector<thread> threads;
    Matrix result(a.rows, b.cols, false);
    for (int i = 0; i < thread_amount; i++) {
        threads.emplace_back(multiplier, ref(a), ref(b), ref(result), thread_amount, i);
    }

    for (auto &t: threads) t.join();
    
    return result;
}