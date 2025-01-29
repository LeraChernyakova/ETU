#ifndef THREADS_MATRIX_ALGORITHMS_H
#define THREADS_MATRIX_ALGORITHMS_H

#include <cstddef>

namespace common
{

class Matrix;

} // namespace common

namespace threads
{

/// @brief Умножение двух матриц (последовательное).
/// @param[in] lhs Умножаемая матрица (левый операнд).
/// @param[in] rhs Матрица, на которую производится умножение (правый операнд).
/// @return Результирующая матрица.
common::Matrix multiplyMatricesSerial( const common::Matrix& lhs, const common::Matrix& rhs );

/// @brief Умножение двух матриц (параллельное).
/// @param[in] lhs Умножаемая матрица (левый операнд).
/// @param[in] rhs Матрица, на которую производится умножение (правый операнд).
/// @param[in] threadsCount Количество потоков.
/// @return Результирующая матрица.
common::Matrix multiplyMatricesParallel( 
    const common::Matrix& lhs, const common::Matrix& rhs, const size_t threadsCount );

} // namespace threads

#endif // THREADS_MATRIX_ALGORITHMS_H
