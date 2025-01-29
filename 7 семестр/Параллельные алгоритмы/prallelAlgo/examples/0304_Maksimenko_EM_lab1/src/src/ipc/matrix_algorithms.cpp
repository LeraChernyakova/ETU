#include "ipc/matrix_algorithms.h"

#include <stdexcept>
#include "common/matrix.h"

common::Matrix ipc::multiplyMatrices( const common::Matrix& lhs, const common::Matrix& rhs )
{
    if ( lhs.columns() != rhs.rows() )
    {
        std::runtime_error{ "Cannot multiply matrices: invalid sizes" };
    }
    common::Matrix result{ lhs.rows(), rhs.columns() };
    for ( size_t row = 0; row < lhs.rows(); ++row )
    {
        for ( size_t column = 0; column < rhs.columns(); ++column )
        {
            result.set( row, column, common::Matrix::multiplyRC( lhs, rhs, row, column ) );
        }
    }
    return result;
} // multiplyMatrices
