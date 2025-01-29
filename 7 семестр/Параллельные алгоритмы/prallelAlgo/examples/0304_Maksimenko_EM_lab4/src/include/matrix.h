#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

namespace lab4
{

template < typename T >
class Matrix
{
public:
    Matrix( size_t rows, size_t cols );

    inline size_t GetRows() const;
    inline size_t GetCols() const;

    inline T Get( size_t row, size_t col ) const;
    inline void Set( size_t row, size_t col, T value );

    Matrix Slice( size_t rows, size_t cols, size_t startRow, size_t startCol ) const;
    void Insert( const Matrix& matrix, size_t startRow, size_t startCol );

    void Print( std::ostream& out ) const;
    static Matrix Read( std::istream& in );
    void RandomFill( T min, T max );
private:
    std::vector< T > data_;
    size_t rows_;
    size_t cols_;

};

template < typename T >
Matrix< T > operator+ ( const Matrix< T >& lhs, const Matrix< T >& rhs );

template < typename T >
Matrix< T > operator- ( const Matrix< T >& lhs, const Matrix< T >& rhs );

template < typename T >
bool operator== ( const Matrix< T >& lhs, const Matrix< T >& rhs );

template <>
bool operator== ( const Matrix< float >& lhs, const Matrix< float >& rhs );

} // namespace lab4

#include "matrix.hpp"

#endif // MATRIX_H
