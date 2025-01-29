#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <thread>
#include <vector>

namespace lab4
{

constexpr size_t strassenLowerBound = 8;

template < typename T >
Matrix< T > Algorithms< T >::MultiplicationSerial( const Matrix< T >& lhs, const Matrix< T >& rhs )
{
    assert( lhs.GetCols() == rhs.GetRows() );

    Matrix< T > result{ lhs.GetRows(), rhs.GetCols() };
    for ( size_t row = 0; row < lhs.GetRows(); ++row )
    {
        for ( size_t col = 0; col < rhs.GetCols(); ++col )
        {
            result.Set( row, col, DotMultiplication( lhs, rhs, row, col ) );
        }
    }
    return result;
} // MultiplicationSerial


template < typename T >
Matrix< T > Algorithms< T >::MultiplicationParallel( const Matrix< T >& lhs, const Matrix< T >& rhs, size_t threads )
{
    assert( lhs.GetCols() == rhs.GetRows() );
    
    std::vector< std::thread > multiplicationThreads;
    multiplicationThreads.reserve( threads );

    Matrix< T > result{ lhs.GetRows(), rhs.GetCols() };

    for ( size_t idx = 0; idx < threads; ++idx )
    {
        multiplicationThreads.emplace_back( [ &result, &lhs, &rhs, idx, threads ]() {
            for ( size_t num = idx; num < lhs.GetRows() * rhs.GetCols(); num += threads )
            {
                size_t row = num / rhs.GetCols();
                size_t col = num % rhs.GetCols();
                result.Set( row, col, DotMultiplication( lhs, rhs, row, col ) );
            }
        } );
    }
    for ( std::thread& t: multiplicationThreads )
    {
        t.join();
    }
    return result;
} // MultiplicationParallel


template < typename T >
void Algorithms< T >::MultiplicationStrassen( const Matrix< T >& lhs
    , const Matrix< T >& rhs, Matrix< T >& res, size_t recursion )
{
    assert( lhs.GetCols() == rhs.GetRows() );
    assert( lhs.GetCols() == lhs.GetRows() ); ///< Матрица квадратная
    assert( 0 == ( lhs.GetCols() & ( lhs.GetCols() - 1 ) ) ); ///< Размер матрицы - степень 2

    size_t half = lhs.GetCols() >> 1;
    if ( half <= strassenLowerBound )
    {
        res = MultiplicationSerial( lhs, rhs );
        return;
    }

    Matrix< T > a11 = lhs.Slice( half, half, 0, 0 );
    Matrix< T > a12 = lhs.Slice( half, half, 0, half );
    Matrix< T > a21 = lhs.Slice( half, half, half, 0 );
    Matrix< T > a22 = lhs.Slice( half, half, half, half );

    Matrix< T > b11 = rhs.Slice( half, half, 0, 0 );
    Matrix< T > b12 = rhs.Slice( half, half, 0, half );
    Matrix< T > b21 = rhs.Slice( half, half, half, 0 );
    Matrix< T > b22 = rhs.Slice( half, half, half, half );

    Matrix< T > d { half, half };
    Matrix< T > d1{ half, half };
    Matrix< T > d2{ half, half };
    Matrix< T > h1{ half, half };
    Matrix< T > h2{ half, half };
    Matrix< T > v1{ half, half };
    Matrix< T > v2{ half, half };

    if ( 0 == recursion ) ///< Параллельное умножение
    {
        std::vector< std::thread > strassenThreads;
        strassenThreads.emplace_back( MultiplicationStrassen
            , a11 + a22, b11 + b22, std::ref( d ), recursion + 1 );
        strassenThreads.emplace_back( MultiplicationStrassen
            , a12 - a22, b21 + b22, std::ref( d1 ), recursion + 1 );
        strassenThreads.emplace_back( MultiplicationStrassen
            , a21 - a11, b11 + b12, std::ref( d2 ), recursion + 1 );
        strassenThreads.emplace_back( MultiplicationStrassen
            , a11 + a12, b22, std::ref( h1 ), recursion + 1 );
        strassenThreads.emplace_back( MultiplicationStrassen
            , a21 + a22, b11, std::ref( h2 ), recursion + 1 );
        strassenThreads.emplace_back( MultiplicationStrassen
            , a22, b21 - b11, std::ref( v1 ), recursion + 1 );
        strassenThreads.emplace_back( MultiplicationStrassen
            , a11, b12 - b22, std::ref( v2 ), recursion + 1 );
        
        for ( std::thread& t: strassenThreads )
        {
            t.join();
        }
    }
    else
    {
        MultiplicationStrassen( a11 + a22, b11 + b22, d, recursion + 1 );
        MultiplicationStrassen( a12 - a22, b21 + b22, d1, recursion + 1 );
        MultiplicationStrassen( a21 - a11, b11 + b12, d2, recursion + 1 );
        MultiplicationStrassen( a11 + a12, b22, h1, recursion + 1 );
        MultiplicationStrassen( a21 + a22, b11, h2, recursion + 1 );
        MultiplicationStrassen( a22, b21 - b11, v1, recursion + 1 );
        MultiplicationStrassen( a11, b12 - b22, v2, recursion + 1 );
    }

    res.Insert( d + d1 + v1 - h1, 0, 0 );
    res.Insert( v2 + h1, 0, half );
    res.Insert( v1 + h2, half, 0 );
    res.Insert( d + d2 + v2 - h2, half, half );
} // MultiplicationStrassen


template < typename T >
T Algorithms< T >::DotMultiplication( const Matrix< T >& lhs, const Matrix< T >& rhs, size_t row, size_t col )
{
    assert( lhs.GetCols() == rhs.GetRows() );
    assert( row < lhs.GetRows() );
    assert( col < rhs.GetCols() );

    T value{};
    for ( size_t p = 0; p < lhs.GetCols(); ++p )
    {
        value += lhs.Get( row, p ) * rhs.Get( p, col );
    }
    return value;
} // DotMultiplication

} // namespace lab4

#endif // ALGORITHMS_HPP
