#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <random>
#include <iomanip>
#include <cassert>


namespace lab4
{

template < typename T >
Matrix< T >::Matrix( size_t rows, size_t cols )
    : data_( rows * cols, T{} )
    , rows_{ rows }
    , cols_{ cols }
{} // Matrix( size_t rows, size_t cols )


template < typename T >
size_t Matrix< T >::GetRows() const
{
    return rows_;
} // GetRows


template < typename T >
size_t Matrix< T >::GetCols() const
{
    return cols_;
} // GetCols


template < typename T >
T Matrix< T >::Get( size_t row, size_t col ) const
{
    assert( row < rows_ );
    assert( col < cols_ );
    return data_[ row * cols_ + col ];
} // Get


template < typename T >
void Matrix< T >::Set( size_t row, size_t col, T value )
{
    assert( row < rows_ );
    assert( col < cols_ );
    data_[ row * cols_ + col ] = value;
} // Set


template < typename T >
Matrix< T > Matrix< T >::Slice( size_t rows, size_t cols, size_t startRow, size_t startCol ) const
{
    assert( startRow < rows_ );
    assert( startCol < cols_ );
    assert( startRow + rows <= rows_ );
    assert( startCol + cols <= cols_ );

    Matrix< T > slice{ rows, cols };
    slice.data_.clear();
    for ( size_t row = startRow; row < startRow + rows; ++row )
    {
        std::copy_n( data_.begin() + row * cols_ + startCol, cols, std::back_inserter( slice.data_ ) );
    }
    return slice;
} // Slice


template < typename T >
void Matrix< T >::Insert( const Matrix< T >& matrix, size_t startRow, size_t startCol )
{
    assert( startRow < rows_ );
    assert( startCol < cols_ );
    assert( startRow + matrix.rows_ <= rows_ );
    assert( startCol + matrix.cols_ <= cols_ );

    for ( size_t row = 0; row < matrix.rows_; ++row )
    {
        for ( size_t col = 0; col < matrix.cols_; ++col )
        {
            size_t mergeRow = row + startRow;
            size_t mergeCol = col + startCol;

            data_[ mergeRow * cols_ + mergeCol ] = matrix.data_[ row * matrix.cols_ + col ];
        }
    }
} // Insert


template < typename T >
void Matrix< T >::Print( std::ostream& out ) const
{
    out << "Matrix " << rows_ << "x" << cols_ << '\n';
    for ( size_t row = 0; row < rows_; ++row )
    {
        for ( size_t col = 0; col < cols_; ++col )
        {
            out << std::left << std::setw( 6 ) << data_[ row * cols_ + col ] << ' ';
        }
        out << '\n';
    }
} // Print


template < typename T >
Matrix< T > Matrix< T >::Read( std::istream& in )
{
    size_t rows;
    size_t cols;
    T value;

    in >> rows >> cols;
    if ( in.eof() || in.fail() )
    {
        throw std::runtime_error{ "No more data to read" };
    }

    Matrix< T > matrix{ rows, cols };
    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t col = 0; col < cols; ++col  )
        {
            if ( in.eof() || in.fail() )
            {
                throw std::runtime_error{ "No more data to read" };
            }
            in >> value;
            matrix.data_[ row * cols + col ] = value;
        }
    }

    return matrix;
} // Read


template < typename T >
void Matrix< T >::RandomFill( T min, T max )
{
    std::random_device rd;
    std::mt19937 re{ rd() };
    std::uniform_real_distribution<> distribution{
        static_cast< double >( min ),
        static_cast< double >( max )
    };

    for ( size_t row = 0; row < rows_; ++row )
    {
        for ( size_t col = 0; col < cols_; ++col )
        {
            data_[ row * cols_ + col ] = static_cast< T >( distribution( re ) );
        }
    }
} // RandomFill


template < typename T >
Matrix< T > operator+ ( const Matrix< T >& lhs, const Matrix< T >& rhs )
{
    assert( lhs.GetCols() == rhs.GetCols() );
    assert( lhs.GetRows() == rhs.GetRows() );

    Matrix< T > result{ lhs.GetRows(), lhs.GetCols() };
    for ( size_t row = 0; row < lhs.GetRows(); ++row )
    {
        for ( size_t col = 0; col < lhs.GetCols(); ++col )
        {
            result.Set( row, col, lhs.Get( row, col ) + rhs.Get( row, col ) );
        }
    }
    return result;
} // operator+


template < typename T >
Matrix< T > operator- ( const Matrix< T >& lhs, const Matrix< T >& rhs )
{
    assert( lhs.GetCols() == rhs.GetCols() );
    assert( lhs.GetRows() == rhs.GetRows() );

    Matrix< T > result{ lhs.GetRows(), lhs.GetCols() };
    for ( size_t row = 0; row < lhs.GetRows(); ++row )
    {
        for ( size_t col = 0; col < lhs.GetCols(); ++col )
        {
            result.Set( row, col, lhs.Get( row, col ) - rhs.Get( row, col ) );
        }
    }
    return result;
} // operator-


template < typename T >
bool operator== ( const Matrix< T >& lhs, const Matrix< T >& rhs )
{
    if ( lhs.GetRows() != rhs.GetRows() || lhs.GetCols() != rhs.GetCols() )
    {
        return false;
    }
    
    for ( size_t row = 0; row < lhs.GetRows(); ++row )
    {
        for ( size_t col = 0; col < lhs.GetCols(); ++col )
        {
            if ( lhs.Get( row, col ) != rhs.Get( row, col ) )
            {
                return false;
            }
        }
    }
    return true;
} // operator== ( const Matrix< T >& lhs, const Matrix< T >& rhs )


template <>
bool operator== ( const Matrix< float >& lhs, const Matrix< float >& rhs )
{
    if ( lhs.GetRows() != rhs.GetRows() || lhs.GetCols() != rhs.GetCols() )
    {
        return false;
    }
    
    constexpr float precision = 0.001f;
    for ( size_t row = 0; row < lhs.GetRows(); ++row )
    {
        for ( size_t col = 0; col < lhs.GetCols(); ++col )
        {
            if ( std::abs( lhs.Get( row, col ) - rhs.Get( row, col ) ) > precision )
            {
                return false;
            }
        }
    }
    return true;
} // operator== ( const Matrix< float >& lhs, const Matrix< float >& rhs )

} // namespace lab4

#endif // MATRIX_HPP
