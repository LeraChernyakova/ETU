#pragma once
#include "Matrix.h"
#include <memory>
#include <future>

class MultiplicationMatrix{
public:
    static MultiplicationMatrix create(Matrix left, Matrix right);
    Matrix multiply();
    std::vector<int> multiplyRow(int i);
    void multiplyRowThread(int i, std::promise<std::vector<int>>& result);
    MultiplicationMatrix(){};
    MultiplicationMatrix(Matrix left, Matrix right) : left(left), right(right){}
private:
    int multiplyColumnRow(int i, int j);
    Matrix left, right;
};