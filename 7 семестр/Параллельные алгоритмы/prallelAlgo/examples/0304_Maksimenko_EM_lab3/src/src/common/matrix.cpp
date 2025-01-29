#include "common/matrix.h"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

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
} // read


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
} // write
