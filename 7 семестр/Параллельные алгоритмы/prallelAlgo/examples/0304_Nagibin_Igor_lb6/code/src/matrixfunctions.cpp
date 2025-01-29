#include "matrixfunctions.hpp"
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>


void printMatrix(Matrix &matrix)
{
    for (const auto &vec : matrix)
    {
        for (auto elem : vec)
        {
            std::cout << static_cast<int>(elem) << ' ';
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
    if (i > result.size() || j > result.size())
        return;

    for (int k = 0; k < result.size(); ++k)
    {
        result[i][j] += (matr1[i][k] * matr2[k][j]);
    }
}

Matrix generateMatrix(size_t size)
{
    Matrix matrix;
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(1, UINT8_MAX);
    for (auto i = 0, val = 0; i < size; ++i)
    {
        matrix.emplace_back();
        for (auto j = 0; j < size; ++j, ++val)
        {
            // matrix.back().push_back(val);
            matrix.back().push_back(dist(rng));
        }
    }
    return std::move(matrix);
}

Matrix addMatrix(Matrix &m1, Matrix &m2)
{
    Matrix res = generateMatrix(m1.size());

    for (auto i = 0; i < m1.size(); ++i)
    {
        for (auto j = 0; j < m1.size(); ++j)
        {
            res[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return std::move(res);
}

Matrix subMatrix(Matrix &m1, Matrix &m2)
{   

    Matrix res = generateMatrix(m1.size());

    for (auto i = 0; i < m1.size(); ++i)
    {
        for (auto j = 0; j < m1.size(); ++j)
        {
            res[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return std::move(res);
}

Matrix multiplyMatrix(Matrix &matrix1, Matrix &matrix2)
{
    Matrix res = generateMatrix(matrix1.size());

    for (auto rowIndex = 0; rowIndex < matrix1.size(); ++rowIndex)
    {
        for (auto colIndex = 0; colIndex < matrix2.size(); ++colIndex)
        {
            res[rowIndex][colIndex] = 0;
            for (auto i = 0; i < matrix1.size(); ++i)
            {
                res[rowIndex][colIndex] += (matrix1[rowIndex][i] * matrix2[i][colIndex]);
            }
        }
    }
    return std::move(res);
}

Matrix slice(Matrix &matrix,
             std::size_t piece,
             std::size_t startRow,
             std::size_t startCol)
{
    auto res = generateMatrix(piece);
    for (auto i = 0; i < res.size(); i++)
    {
        std::copy_n(matrix[startCol].begin(), piece, res[i].begin());
        // std::copy(matrix[startCol + i].begin() + startRow,
                //   matrix[startCol + i].begin() + startRow + piece,
                //   res[i].begin());
    }
    return std::move(res);
}

void insert(Matrix &matrix, Matrix &matrixToInsert, std::size_t startRow, std::size_t startCol)
{   
    auto insertIndex = 0;
    for (auto i = startCol; i < matrixToInsert.size(); i++, insertIndex++)
    {
        std::copy(matrixToInsert[insertIndex].begin(), matrixToInsert[insertIndex].end(), matrix[i].begin());
    }
}


