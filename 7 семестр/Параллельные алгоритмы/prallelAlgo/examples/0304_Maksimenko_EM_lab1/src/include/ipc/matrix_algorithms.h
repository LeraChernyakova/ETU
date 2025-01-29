#ifndef IPC_MATRIX_ALGORITHMS_H
#define IPC_MATRIX_ALGORITHMS_H

namespace common
{

class Matrix;

} // namespace common

namespace ipc
{

/// @brief Умножение двух матриц.
/// @param[in] lhs Умножаемая матрица (левый операнд).
/// @param[in] rhs Матрица, на которую производится умножение (правый операнд).
/// @return Результирующая матрица.
common::Matrix multiplyMatrices( const common::Matrix& lhs, const common::Matrix& rhs );

} // namespace ipc

#endif // IPC_MATRIX_ALGORITHMS_H
