#include "matrix.h"

using namespace std;

Matrix::Matrix(int rows, int cols) {
    mRows = rows;
    mCols = cols;

    matrix = vector<vector<int>>(rows);
    for (int row=0; row < mRows; row++) {
        matrix[row] = vector<int>(mCols, 0);
    }
};

Matrix::Matrix(int rows, int cols, int rndMin, int rndMax): Matrix::Matrix(rows, cols) {
    Matrix::randomInit(rndMin, rndMax);
};

Matrix::Matrix(const Matrix& secondMat) {
    mRows = secondMat.mRows;
    mCols = secondMat.mCols;
    matrix = secondMat.matrix;
};

Matrix::Matrix(const Matrix&& secondMat) {
    mRows = secondMat.mRows;
    mCols = secondMat.mCols;
    matrix = move(secondMat.matrix);
};

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
};

int Matrix::getRows() {
    return mRows;
};

int Matrix::getCols() {
    return mCols;
};

vector<int>& Matrix::operator[](int index) {
    return matrix[index];
}

Matrix Matrix::operator+(const Matrix& secondMat) {
    Matrix resultMat(mRows, mCols);
    if (mRows == secondMat.mRows || mCols == secondMat.mCols) {
        for (int row=0; row < mRows; row++) {
            for (int col=0; col < mCols; col++) {
                resultMat.matrix[row][col] = matrix[row][col] + secondMat.matrix[row][col];
            }
        }
    } else {
        cout << "+: Matrices dimensions don't match." << endl;
    }
    return resultMat;
};

Matrix Matrix::operator-(const Matrix& secondMat) {
    Matrix resultMat(mRows, mCols);
    if (mRows == secondMat.mRows || mCols == secondMat.mCols) {
        for (int row=0; row < mRows; row++) {
            for (int col=0; col < mCols; col++) {
                resultMat.matrix[row][col] = matrix[row][col] - secondMat.matrix[row][col];
            }
        }
    } else {
        cout << "-: Matrices dimensions don't match." << endl;
    }
    return resultMat;
};

Matrix Matrix::operator*(const Matrix& secondMat) {
    Matrix resultMat(mRows, secondMat.mCols);
    if (mCols == secondMat.mRows) {
        for (int i=0; i < mRows; i++) {
            for (int j=0; j < mCols; j++) {
                for (int k=0; k < secondMat.mCols; k++) {
                    resultMat.matrix[i][k] += (matrix[i][j] * secondMat.matrix[j][k]);
                }
            }
        }
    } else {
        cout << "*: Matrices dimensions don't match." << endl;
    }
    return resultMat;
};

bool Matrix::operator==(Matrix& secondMat) {
    if (mRows != secondMat.mRows || mCols != secondMat.mCols) {
        return false;
    }

    for (int row=0; row < mRows; row++) {
        for (int col=0; col < mCols; col++) {
            if (matrix[row][col] != secondMat.matrix[row][col]) {
                return false;
            }
        }
    }

    return true;
}

void Matrix::operator=(const Matrix&& secondMat) {
    mRows = secondMat.mRows;
    mCols = secondMat.mCols;
    matrix = move(secondMat.matrix);
}

vector<int> Matrix::multiplyRow(Matrix& firstMat, Matrix& secondMat, int rowInd) {
    vector<int> result(secondMat.mCols);

    // Получаем строку результата умножения матриц.
    for (int sCol=0; sCol < secondMat.mCols; sCol++) {
        for (int fCol=0; fCol < firstMat.mCols; fCol++) {
            result[sCol] += firstMat.matrix[rowInd][fCol] * secondMat.matrix[fCol][sCol];
        }
    }

    return result;
};

void Matrix::printMatrix() {
    for (int row=0; row < mRows; row++) {
        for (int col=0; col < mCols; col++) {
            cout << matrix[row][col] << "\t";
        }
        cout << endl;
    }
};

void Matrix::writeMatrix(string& fileName) {
    fstream outFile;
    outFile.open(fileName, ios::out | ios::trunc);

    for (int row=0; row < mRows; row++) {
        for (int col=0; col < mCols; col++) {
            outFile << matrix[row][col] << " ";
        }
        outFile << endl;
    }

    outFile.close();
};