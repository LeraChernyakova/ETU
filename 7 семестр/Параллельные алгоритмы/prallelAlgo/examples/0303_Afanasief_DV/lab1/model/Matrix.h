#pragma once
#include <vector>
#include <utility>
#include <iostream>
struct Matrix
{
    std::pair<unsigned int, unsigned int> size() const;
    std::vector<std::vector<int>> m;
    static Matrix generate();
    static Matrix generate(int size);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& obj);
    static std::pair<Matrix, int*> readFromPtr(int* ptr);
    int* writeToPtr(int* ptr) const;
};
