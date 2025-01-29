#pragma once
#include "Matrix.h"
#include <memory>
#include <future>
#include <utility>

class MultiplicationMatrix{
public:
    static MultiplicationMatrix create(const Matrix& left, const Matrix& right);
    Matrix multiplyParallel(int threads);
    Matrix multiplyScalable(int threads);
    Matrix multiplyStrassen();
private:
    std::vector<int> multiplyRow(int i);
    void scalable(Matrix& result, int index, int threads);
    int multiplyColumnRow(int i, int j);
    MultiplicationMatrix()= default;
    MultiplicationMatrix(Matrix left, Matrix right) : left(std::move(left)), right(std::move(right)){}
    void recursive(Matrix left, Matrix right, Matrix &result, int d = 1);
    std::vector<Matrix> split(Matrix matrix);
    Matrix left, right;
};