#include "threads/matrix_algorithms.h"

#include <stdexcept>
#include <thread>
#include <vector>
#include <random>
#include "common/matrix.h"


common::Matrix threads::generateMatrix( size_t rows, size_t columns )
{
    common::Matrix matrix{ rows, columns };

    std::random_device rd;
    std::mt19937 re{ rd() };
    std::uniform_real_distribution<> distribution{ -3.0f, 3.0f };

    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t column = 0; column < columns; ++column )
        {
            matrix.set( row, column, distribution( re ) );
        }
    }
    return matrix;
} // generateMatrix


common::Matrix threads::multiplyMatricesSerial( const common::Matrix& lhs, const common::Matrix& rhs )
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
} // multiplyMatricesSerial


common::Matrix threads::multiplyMatricesParallel(
    const common::Matrix& lhs, const common::Matrix& rhs, const size_t threadsCount )
{
    if ( lhs.columns() != rhs.rows() )
    {
        std::runtime_error{ "Cannot multiply matrices: invalid sizes" };
    }
    common::Matrix result{ lhs.rows(), rhs.columns() };

    std::vector< std::thread > multiplyThreads;
    multiplyThreads.reserve( lhs.columns() );

    for ( size_t n = 0; n < threadsCount; ++n )
    {
        multiplyThreads.emplace_back( [ &lhs, &rhs, &result, n, threadsCount ]() {
            for ( size_t row = 0; row < lhs.rows(); ++row )
            {
                for ( size_t column = 0; column < rhs.columns(); ++column )
                {
                    if ( n == ( ( row + column ) % threadsCount ) )
                    {
                        result.set( row, column, common::Matrix::multiplyRC( lhs, rhs, row, column ) );
                    }
                }
            }
        } );
    }

    for ( auto& thread: multiplyThreads )
    {
        thread.join();
    }
    return result;
} // multiplyMatricesParallel
