#include "matrixfunctions.hpp"
#include <random>
void printMatrix(Matrix &matrix)
{
    for (const auto &vec : matrix)
    {
        for (auto elem : vec)
        {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "End of vmatrix;\n";
}

void multiplyVectorMatrixRow(std::size_t i,
                             std::size_t j,
                             Matrix &matr1,
                             Matrix &matr2,
                             Matrix &result)
{   
    if(i > result.size() || j > result.size()) return ;

    for (int k = 0; k < result.size(); ++k)
    {
        result[i][j] += (matr1[i][k] * matr2[k][j]);
    }
}

Matrix generateMatrix(size_t size)
{
    Matrix matrix;
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,999);
    for (auto i = 0, val = 0; i < size; ++i)
    {
        matrix.emplace_back();
        for (auto j = 0; j < size; ++j, ++val)
        {
            matrix.back().push_back(dist6(rng));
        }
    }
    return std::move(matrix);
}