#include "Square_matrix.h"

Square_matrix::Square_matrix(int size): size(size) {
    for (int i = 0; i < size; ++i) {
        matrix.emplace_back(size);
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = 0;
        }
    }
}

void Square_matrix::set_data(int value, int i, int j) {
    matrix[i][j] = value;
}

int Square_matrix::get_data(int i, int j) const {
    return matrix[i][j];
}


int Square_matrix::get_size() const {
    return size;
}

Square_matrix operator+(const Square_matrix &first, const Square_matrix &second) {
    Square_matrix result(first.get_size());

    for (int i = 0; i < first.get_size(); ++i) {
        for (int j = 0; j < second.get_size(); ++j) {
            result.set_data(first.get_data(i, j) + second.get_data(i, j), i, j);
        }
    }

    return result;
}

Square_matrix operator-(const Square_matrix &first, const Square_matrix &second) {
    Square_matrix result(first.get_size());

    for (int i = 0; i < first.get_size(); ++i) {
        for (int j = 0; j < second.get_size(); ++j) {
            result.set_data(first.get_data(i, j) - second.get_data(i, j), i, j);
        }
    }

    return result;
}

bool operator==(const Square_matrix &first, const Square_matrix &second) {
    for (int i = 0; i < first.get_size(); ++i) {
        for (int j = 0; j < second.get_size(); ++j) {
            if (first.get_data(i, j) != second.get_data(i, j))
                return false;
        }
    }

    return true;
}


