#include "matrix.h"

using namespace std;

Matrix::Matrix(int rows, int cols) {
    mRows = rows;
    mCols = cols;

    matrix = vector<vector<int>>(rows);
    for (int row=0; row < mRows; row++) {
        matrix[row] = vector<int>(mCols);
    }
};

Matrix::Matrix(int rows, int cols, int rndMin, int rndMax): Matrix::Matrix(rows, cols) {
    Matrix::randomInit(rndMin, rndMax);
};

void Matrix::printMatrix() {
    for (int row=0; row < mRows; row++) {
        for (int col=0; col < mCols; col++) {
            cout << matrix[row][col] << "\t";
        }
        cout << endl;
    }
};

int* Matrix::serialize() {
    int* buf = new int[mRows * mCols];
    int i=0;
    for(int row = 0; row < mRows; row++) {
        for(int col = 0; col < mCols; col++) {
            buf[i] = matrix[row][col];
            i++;
        }
    }
    return buf;
}

void Matrix::deserialize(int* buf) {
    int i=0;
    for(int row=0; row < mRows; row++) {
        for(int col=0; col < mCols; col++) {
            matrix[row][col] = buf[i];
            i++;
        }
    }
}

vector<int> Matrix::multiplyRow(Matrix& firstMat, Matrix& secondMat, int rowNum) {
    vector<int> result(secondMat.mCols);

    // Получаем строку результата умножения матриц.
    for (int sCol=0; sCol < secondMat.mCols; sCol++) {
        for (int fCol=0; fCol < firstMat.mCols; fCol++) {
            result[sCol] += firstMat.matrix[rowNum][fCol] * secondMat.matrix[fCol][sCol];
        }
    }

    return result;
};

void Matrix::writeMatrix(string& fileName) {
    fstream outFile;
    outFile.open(fileName, ios::out | ios::app);
    outFile << endl << "*************************" << endl;

    for (int row=0; row < mRows; row++) {
        for (int col=0; col < mCols; col++) {
            outFile << matrix[row][col] << " ";
        }
        outFile << endl;
    }

    outFile.close();
};

int Matrix::getRows() {
    return mRows;
};

int Matrix::getCols() {
    return mCols;
};

void Matrix::setRow(int rowNum, vector<int>& row) {
    matrix[rowNum] = row;
}

void Matrix::randomInit(int rndMin, int rndMax) {
    // Инициализируем рандомную генерацию.
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(rndMin, rndMax);

    for (int row=0; row < mRows; row++) {
        for (int col=0; col < mCols; col++) {
            matrix[row][col] = distribution(generator);
        }
    }
}