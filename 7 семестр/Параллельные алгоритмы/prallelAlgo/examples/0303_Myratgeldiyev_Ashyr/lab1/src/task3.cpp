#include "task3.h"
#define MOD 200
#define FILENAME "matrices.txt"
#define OUTPUT_FILE "result3.txt"

typedef unsigned long ul;

int calcEl(MATRIX& m1, MATRIX& m2, PAIR_INT& ij) {
    int length = m2.size();
    int res = 0;
    for (int k = 0; k < length; k++) {
        res += (m1[ij.first][k] * m2[k][ij.second]);
    }
    return res;
}

void threadCalc(MATRIX& m1, MATRIX& m2, MATRIX& res, int thread_count, int num) {
    int rows = m1.size(), cols = m2[0].size();
    int i, j;
    for (int step = num; step < rows * cols; step += thread_count) {
        i = step /  cols;
        j = step % cols;
        res[i][j] = calcEl(m1, m2, make_pair(i, j));
    }


}

void parallelMult(promise<MATRIX>&& prom, MATRIX& m1, MATRIX& m2, int thread_count) {
    PAIR_INT new_dim(m1.size(), m2[0].size());
    int new_size = new_dim.first * new_dim.second;

    if (thread_count <= 0 || thread_count > new_size) {
        cerr << "Invalid thread count\n";
        prom.set_value(MATRIX(1, vector<int>(1)));
        return;
    }

    MATRIX result(new_dim.first, vector<int>(new_dim.second));
    vector<thread> threads;
    for (int i = 0; i < thread_count; i++) {
        thread t(threadCalc, ref(m1), ref(m2), ref(result), ref(thread_count), i);
        threads.emplace_back(move(t));
    }

    for (auto &t: threads) {
        t.join();
    }
    prom.set_value(result);

}

MATRIX calculate(int thread_count, PAIR_INT dim1, PAIR_INT dim2, unsigned long &diff) {
	generateTxtFile(FILENAME, dim1, dim2);
	MATRIX matrix1(dim1.first, vector<int>(dim1.second)),
						matrix2(dim2.first, vector<int>(dim2.second));
	
	thread t1(readMatricesFromFile, FILENAME, ref(matrix1), ref(matrix2));


    promise<MATRIX> matrixMultPromise;
    future<MATRIX> matrixMultFuture = matrixMultPromise.get_future();

    t1.join();

    auto start = chrono::steady_clock::now();
    thread t2(parallelMult, move(matrixMultPromise), ref(matrix1), ref(matrix2), thread_count);
    MATRIX res = matrixMultFuture.get();
    auto finish = chrono::steady_clock::now();
    diff = chrono::duration_cast<chrono::microseconds>(finish - start).count();
    t2.join();
    return res;  //MATRIX(1, vector<int>());
}


int main() {
    unsigned long ms;
    int thread_num;
    int rows1, cols1, rows2, cols2;
    cout << "Enter thread num: ";
    cin >> thread_num;
    cout << "Enter the dimension of the first matrix (rows, cols): ";
    cin >> rows1 >> cols1;
    cout << "Enter the dimension of the second matrix (rows, cols): ";
    cin >> rows2 >> cols2;
    MATRIX res = calculate(thread_num, make_pair(rows1, cols1), make_pair(rows2, cols2), ms);
    cout << "ms: " << ms << '\n';
    printMatrixToFile(OUTPUT_FILE, res);

    return 0;
}

