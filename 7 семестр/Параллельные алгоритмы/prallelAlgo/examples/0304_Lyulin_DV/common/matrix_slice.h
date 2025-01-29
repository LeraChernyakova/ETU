#ifndef MATRIX_SLICE_H
#define MATRIX_SLICE_H

#include <matrix.h>

/// @brief Ссылка на участок матрицы (как std::string_view для std::string).
class MatrixSlice
{
public:
     MatrixSlice( const Matrix& matr );  // implicit
     MatrixSlice( const Matrix& matr, size_t start_row, size_t start_col, size_t rows, size_t cols );
     size_t get_rows() const;
     size_t get_cols() const;
     float get( size_t i, size_t j ) const;
     operator Matrix() const;

private:
     const Matrix& matr_;
     size_t start_row_;
     size_t start_col_;
     size_t rows_;
     size_t cols_;
};

Matrix operator+( const MatrixSlice& lhs, const MatrixSlice& rhs );
Matrix operator-( const MatrixSlice& lhs, const MatrixSlice& rhs );
Matrix operator*( const MatrixSlice& lhs, const MatrixSlice& rhs );

#endif // MATRIX_SLICE_H