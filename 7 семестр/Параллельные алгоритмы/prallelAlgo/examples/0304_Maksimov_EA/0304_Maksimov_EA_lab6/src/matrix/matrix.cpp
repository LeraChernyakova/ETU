#include "matrix.h"

int* generateMatrixPlainArray(int rows, bool isEmpty) {
    int* plainArray = new int[rows*rows];
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            plainArray[i*rows+j] = (isEmpty) ? 0 : rand() % MATRIX_MAX_VALUE;
        }
    }

    return plainArray;
}
