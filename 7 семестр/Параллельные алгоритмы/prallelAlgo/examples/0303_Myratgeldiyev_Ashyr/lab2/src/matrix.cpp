#include "matrix.h"



int calcElement(const vector<vector<int>>& left, const vector<vector<int>>& right, int i, int j) {
        int length = right.size();
        int ans = 0;
        for (int k = 0; k < length; k++) {
            ans += (left[i][k] * right[k][j]);
        }
        return ans;
    }

void parallelMult(const vector<vector<int>>& left,  const vector<vector<int>>& right, vector<vector<int>>& res, const int thread_count, const int num) {
        int newRows = res.size(), newCols = res[0].size();
        int i, j;
        for (int step = num; step < newRows * newCols; step += thread_count) {
            i = step / newCols;
            j = step % newCols;
            res[i][j] = calcElement(left, right, i, j);
        }
    }


//constructor
Matrix::Matrix(int r, int c) : rows(r), cols(c), matrix(r, std::vector<int>(c)) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
		    matrix[i][j] = rand() % 50 - 25;
	    }
    }
}
Matrix::Matrix(const Matrix& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
}

Matrix::Matrix(const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}

Matrix Matrix::operator* (const Matrix& other) {
    vector<thread> my_threads;
    Matrix result(this->rows, other.cols);
    for (int i = 0; i < MULT_THREAD_COUNT; i++) {
        my_threads.emplace_back(parallelMult, ref(this->matrix), ref(other.matrix), ref(result.matrix), MULT_THREAD_COUNT, i);
    }
    for (auto &t: my_threads) {
       t.join();
    }
    return result;
}

void Matrix::operator= (const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
    // this = &other;
}

void Matrix::printMatrix() {
    for (auto &r : matrix) {
        for (auto &el : r) {
            cout << el << ' ';
        }
        cout << '\n';
    }
}

std::ostream& operator<< (std::ostream& os, const Matrix& m) {
    os << m.rows << ' ' << m.cols << '\n';
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.matrix[i][j];
            if (j + 1 < m.cols) os << ' ';
        }
        os << '\n';
    }
    // os << '\n';
    return os;
}

