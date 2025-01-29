#include "matrix.hpp"

using namespace std;

Matrix::Matrix(int rows, int cols) {
    m_rows = rows;
    m_cols = cols;

    matrix = vector<int>(m_rows * m_cols);
};

Matrix::Matrix(int rows, int cols, int rndMin, int rndMax): Matrix::Matrix(rows, cols) {
    Matrix::random_init(rndMin, rndMax);
};

Matrix::Matrix(const Matrix& second_mat) {
    m_rows = second_mat.m_rows;
    m_cols = second_mat.m_cols;
    matrix = second_mat.matrix;
};

Matrix::Matrix(const Matrix&& second_mat) {
    m_rows = second_mat.m_rows;
    m_cols = second_mat.m_cols;
    matrix = move(second_mat.matrix);
};

void Matrix::random_init(int rndMin, int rndMax) {
    // Инициализируем рандомную генерацию.
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(rndMin, rndMax);

    for (int row=0; row < m_rows; row++) {
        for (int col=0; col < m_cols; col++) {
            (*this)(row, col) = distribution(generator);
        }
    }
};

int Matrix::getRows() {
    return m_rows;
};

int Matrix::getCols() {
    return m_cols;
};

int& Matrix::operator() (int row_ind, int col_ind) {
    return matrix[m_cols*row_ind + col_ind];
}

int Matrix::operator() (int row_ind, int col_ind) const {
    return matrix[m_cols*row_ind + col_ind];
}

Matrix Matrix::operator+(const Matrix& second_mat) {
    Matrix result(m_rows, m_cols);
    if (m_rows == second_mat.m_rows || m_cols == second_mat.m_cols) {
        for (int row=0; row < m_rows; row++) {
            for (int col=0; col < m_cols; col++) {
                result(row, col) = (*this)(row, col) + second_mat(row, col);
            }
        }
    } else {
        cout << "+: Matrices dimensions don't match." << endl;
    }
    return result;
};

Matrix Matrix::operator-(const Matrix& second_mat) {
    Matrix result(m_rows, m_cols);
    if (m_rows == second_mat.m_rows || m_cols == second_mat.m_cols) {
        for (int row=0; row < m_rows; row++) {
            for (int col=0; col < m_cols; col++) {
                result(row, col) = (*this)(row, col) - second_mat(row, col);
            }
        }
    } else {
        cout << "-: Matrices dimensions don't match." << endl;
    }
    return result;
};

Matrix Matrix::operator*(const Matrix& second_mat) {
    Matrix result(m_rows, second_mat.m_cols);
    if (m_cols == second_mat.m_rows) {
        for (int i=0; i < m_rows; i++) {
            for (int j=0; j < m_cols; j++) {
                for (int k=0; k < second_mat.m_cols; k++) {
                    result(i, k) += ((*this)(i, j) * second_mat(j, k));
                }
            }
        }
    } else {
        cout << "*: Matrices dimensions don't match." << endl;
    }
    return result;
};

bool Matrix::operator==(Matrix& second_mat) {
    if (m_rows != second_mat.m_rows || m_cols != second_mat.m_cols) {
        return false;
    }

    for (int row=0; row < m_rows; row++) {
        for (int col=0; col < m_cols; col++) {
            if ((*this)(row, col) != second_mat(row, col)) {
                return false;
            }
        }
    }

    return true;
}

void Matrix::operator=(const Matrix&& second_mat) {
    m_rows = second_mat.m_rows;
    m_cols = second_mat.m_cols;
    matrix = move(second_mat.matrix);
}

void Matrix::print_matrix() {
    for (int row=0; row < m_rows; row++) {
        for (int col=0; col < m_cols; col++) {
            cout << (*this)(row, col) << "\t";
        }
        cout << endl;
    }
};

void Matrix::write_matrix(string& file_name) {
    fstream out_file;
    out_file.open(file_name, ios::out | ios::trunc);

    for (int row=0; row < m_rows; row++) {
        for (int col=0; col < m_cols; col++) {
            out_file << (*this)(row, col) << " ";
        }
        out_file << endl;
    }

    out_file.close();
};

int* Matrix::to_pointer() {
    return matrix.data();
}