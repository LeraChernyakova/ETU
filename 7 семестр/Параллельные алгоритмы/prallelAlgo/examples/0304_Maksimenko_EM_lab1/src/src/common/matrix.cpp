#include "common/matrix.h"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "ipc/socket.h"

common::Matrix::Matrix( size_t rows, size_t columns )
    : rows_{ rows }, columns_{ columns }
{
    data_.resize( rows_ * columns_, 0.f );
} // Matrix( size_t rows, size_t columns )


float common::Matrix::get( size_t row, size_t column ) const
{
    if ( row >= rows_ || column >= columns_ )
    {
        throw std::out_of_range{ "Out of range" };
    }
    return data_[ row * columns_ + column ];
} // get


void common::Matrix::set( size_t row, size_t column, float el )
{
    if ( row >= rows_ || column >= columns_ )
    {
        throw std::out_of_range{ "Out of range" };
    }
    data_[ row * columns_ + column ] = el;
} // set


float common::Matrix::multiplyRC( const Matrix& lhs, const Matrix& rhs, size_t row, size_t column )
{
    if ( lhs.columns() != rhs.rows() )
    {
        throw std::out_of_range{ "Invalid matrices size" };
    }
    if ( lhs.rows() <= row || rhs.columns() <= column )
    {
        throw std::out_of_range{ "Out of range" };
    }

    float element = 0.f;
    for ( size_t p = 0; p < lhs.columns(); ++p )
    {
        element += lhs.get( row, p ) * rhs.get( p, column );
    }
    return element;
} // multiplyRC


bool common::Matrix::read( Matrix& matrix, std::istream& stream )
{
    size_t rows;
    size_t columns;
    float element;

    stream >> rows >> columns;
    if ( stream.eof() || stream.fail() )
    {
        return false;
    }

    matrix = Matrix( rows, columns );
    for ( size_t i = 0; i < rows; ++i )
    {
        for ( size_t j = 0; j < columns; ++j  )
        {
            if ( stream.eof() || stream.fail() )
            {
                return false;
            }
            stream >> element;
            matrix.set( i, j, element );
        }
    }

    return true;
} // read( Matrix& matrix, std::istream& stream )


bool common::Matrix::read( Matrix& matrix, ipc::Socket& socket )
{
    size_t size[ 2 ];

    ssize_t sizeNeeded = 2 * sizeof( size_t );
    ssize_t readResult;

    readResult = socket.read( size, 2 );
    if ( sizeNeeded != readResult )
    {
        return false;
    }

    matrix = Matrix( size[ 0 ], size[ 1 ] );
    sizeNeeded = size[ 0 ] * size[ 1 ] * sizeof( float );

    readResult = socket.read( matrix.data(), size[ 0 ] * size[ 1 ] );
    if ( sizeNeeded != readResult )
    {
        return false;
    }

    return true;
} // read( Matrix& matrix, ipc::Socket& socket )


bool common::Matrix::write( const Matrix& matrix, std::ostream& stream )
{
    stream << matrix.rows() << " " << matrix.columns() << '\n';
    if ( stream.fail() )
    {
        return false;
    }

    for ( size_t i = 0; i < matrix.rows(); ++i )
    {
        for ( size_t j = 0; j < matrix.columns(); ++j  )
        {
            if ( stream.fail() )
            {
                return false;
            }
            stream << std::setw( 10 ) << std::setprecision( 3 ) 
                   << std::fixed << matrix.get( i, j );
        }
        stream << '\n';
    }

    return true;
} // write( const Matrix& matrix, std::ofstream& stream )


bool common::Matrix::write( const Matrix& matrix, ipc::Socket& socket )
{
    ssize_t writeResult;
    const size_t size[ 2 ] = { matrix.rows(), matrix.columns() };
    ssize_t sizeNeeded = 2 * sizeof( size_t );

    writeResult = socket.write( size, 2 );
    if ( sizeNeeded != writeResult )
    {
        return false;
    }

    sizeNeeded = size[ 0 ] * size[ 1 ] * sizeof( float );
    writeResult = socket.write( matrix.data(), size[ 0 ] * size[ 1 ] );
    if ( sizeNeeded != writeResult )
    {
        return false;
    }

    return true;
} // write( const Matrix& matrix, ipc::Socket& socket )
