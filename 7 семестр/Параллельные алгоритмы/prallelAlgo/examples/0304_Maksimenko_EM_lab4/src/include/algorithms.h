#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "matrix.h"

namespace lab4
{

template < typename T >
class Algorithms
{
public:
    static Matrix< T > MultiplicationSerial(   const Matrix< T >& lhs, const Matrix< T >& rhs );
    static Matrix< T > MultiplicationParallel( const Matrix< T >& lhs, const Matrix< T >& rhs, size_t threads );
    static void MultiplicationStrassen( const Matrix< T >& lhs
        , const Matrix< T >& rhs, Matrix< T >& res, size_t recursion = 0 );

    static T DotMultiplication( const Matrix< T >& lhs, const Matrix< T >& rhs, size_t row, size_t col );
};

} // namespace lab4

#include "algorithms.hpp"

#endif // ALGORITHMS_H
