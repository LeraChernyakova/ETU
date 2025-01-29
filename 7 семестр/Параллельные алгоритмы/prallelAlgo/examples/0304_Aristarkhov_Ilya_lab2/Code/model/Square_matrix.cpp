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

int Square_matrix::get_data(int i, int j) {
    return matrix[i][j];
}


int Square_matrix::get_size() const {
    return size;
}


