#include "MultiplicationMatrix.h"

MultiplicationMatrix MultiplicationMatrix::create(const Matrix& left, const Matrix& right){
    
    if(left.size().second != right.size().first){
        throw std::runtime_error("Wrong size matrix");
    }
    return {left, right};
    
}
int MultiplicationMatrix::multiplyColumnRow(int i, int j){
    int result = 0;
    for(int iter = 0; iter < this->left.size().second; iter++) {
        result += this->left.m[i][iter] * this->right.m[iter][j];
    }
    return result;
}

std::vector<int> MultiplicationMatrix::multiplyRow(int i){
    std::vector<int> result;
    for(int iter = 0; iter < this->right.size().second; iter++) {
        result.emplace_back(this->multiplyColumnRow(i, iter));
    }
    return result;
}
Matrix MultiplicationMatrix::multiplyParallel(int threads){
    Matrix resultMatrix;
    for (int i = 0; i < left.size().first; i += threads) {
        int count = threads;
        if (count + i > left.size().first) {
            count = left.size().first - i;
        }
        std::vector<std::future<std::vector<int>>> futures;
        for (int j = 0; j < count; j++) {
            futures.push_back(std::async(std::launch::async, &MultiplicationMatrix::multiplyRow, this, i + j));
        }
        for (auto &res: futures) {
            resultMatrix.m.push_back(res.get());
        }
    }
    return resultMatrix;
}

Matrix MultiplicationMatrix::multiplyScalable(int threads){
    Matrix result(left.size().first, right.size().second);
    for(int i = 0; i < threads; i++)
        std::async(std::launch::async, &MultiplicationMatrix::scalable, this, std::ref(result), i, threads);
    return result;
}

void MultiplicationMatrix::scalable(Matrix& result, int index, int threads){
    for (int l = index; l < result.size().first*result.size().second; l += threads) {
        int i = l / result.size().first;
        int j = l % result.size().first;
        int sum = 0;
        for (int h = 0; h < result.size().first; h++) {
            sum += (left.m[i][h] * right.m[h][j]);
        }
        result.m[i][j] = sum;
    }
}
Matrix MultiplicationMatrix::multiplyStrassen(){
    Matrix result(left.size().first,right.size().second);
    unsigned size = result.size().first / 2;
    Matrix P1 = Matrix(size, size);
    Matrix P2 = Matrix(size, size);
    Matrix P3 = Matrix(size, size);
    Matrix P4 = Matrix(size, size);
    Matrix P5 = Matrix(size, size);
    Matrix P6 = Matrix(size, size);
    Matrix P7 = Matrix(size, size);
    std::vector<Matrix> left_splited = split(left);
    std::vector<Matrix> rigth_splited = split(right);
    /*
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[0] + left_splited[3], rigth_splited[0] + rigth_splited[3], std::ref(P1));
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[2] + left_splited[3], rigth_splited[0], std::ref(P2));
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[0], rigth_splited[1] - rigth_splited[3], std::ref(P3));
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[3], rigth_splited[2] - rigth_splited[0], std::ref(P4));
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[0] + left_splited[1], rigth_splited[3], std::ref(P5));
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[2] - left_splited[0], rigth_splited[0] + rigth_splited[1], std::ref(P6));
    std::async(std::launch::async, &MultiplicationMatrix::recursive, this, left_splited[1] - left_splited[3], rigth_splited[2] + rigth_splited[3], std::ref(P7));
    */

    recursive(left_splited[0] + left_splited[3], rigth_splited[0] + rigth_splited[3], P1);
    recursive(left_splited[2] + left_splited[3], rigth_splited[0], P2);
    recursive(left_splited[0], rigth_splited[1] - rigth_splited[3], P3);
    recursive(left_splited[3], rigth_splited[2] - rigth_splited[0], P4);
    recursive(left_splited[0] + left_splited[1], rigth_splited[3], P5);
    recursive(left_splited[2] - left_splited[0], rigth_splited[0] + rigth_splited[1], P6);
    recursive(left_splited[1] - left_splited[3], rigth_splited[2] + rigth_splited[3], P7);
    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.m[i][j] = C11.m[i][j];
            result.m[i][size + j] = C12.m[i][j];
            result.m[size + i][j] = C21.m[i][j];
            result.m[size + i][size + j] = C22.m[i][j];
        }
    }
    return result;
}
void MultiplicationMatrix::recursive(Matrix left, Matrix right, Matrix &result, int d) {
    unsigned size = result.size().first / 2;
    if (size <= 2 || d <= 3) {
        MultiplicationMatrix M = MultiplicationMatrix::create(left,right);
        result = M.multiplyScalable(1);
        return;
    }
    Matrix P1(size, size);
    Matrix P2(size, size);
    Matrix P3(size, size);
    Matrix P4(size, size);
    Matrix P5(size, size);
    Matrix P6(size, size);
    Matrix P7(size, size);
    std::vector<Matrix> left_splited = split(left);
    std::vector<Matrix> rigth_splited = split(right);
    recursive(left_splited[0] + left_splited[3], rigth_splited[0] + rigth_splited[3], P1, d+1);
    recursive(left_splited[2] + left_splited[3], rigth_splited[0], P2, d+1);
    recursive(left_splited[0], rigth_splited[1] - rigth_splited[3], P3, d+1);
    recursive(left_splited[3], rigth_splited[2] - rigth_splited[0], P4, d+1);
    recursive(left_splited[0] + left_splited[1], rigth_splited[3], P5, d+1);
    recursive(left_splited[2] - left_splited[0], rigth_splited[0] + rigth_splited[1], P6, d+1);
    recursive(left_splited[1] - left_splited[3], rigth_splited[2] + rigth_splited[3], P7, d+1);
    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.m[i][j] = C11.m[i][j];
            result.m[i][size + j] = C12.m[i][j];
            result.m[size + i][j] = C21.m[i][j];
            result.m[size + i][size + j] = C22.m[i][j];
        }
    }
}

std::vector<Matrix> MultiplicationMatrix::split(Matrix matrix) {
    unsigned size = matrix.size().first / 2;
    Matrix A = Matrix(size, size);
    Matrix B = Matrix(size, size);
    Matrix C = Matrix(size, size);
    Matrix D = Matrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A.m[i][j] = matrix.m[i][j];
            B.m[i][j] = matrix.m[i][size + j];
            C.m[i][j] = matrix.m[size + i][j];
            D.m[i][j] = matrix.m[size + i][size + j];
        }
    }
    return {A, B, C, D};
}