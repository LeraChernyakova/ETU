#include <matrix.h>
#include <cstdlib>
#include <cassert>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <functional>

#include <matrix_slice.h>

namespace
{

constexpr static size_t defaultThreadCount = 4;


void task_v1( const Matrix& lhs, const Matrix& rhs, Matrix& result, size_t n, size_t count )
{
     for ( size_t pos = 0; pos < lhs.get_rows(); pos++ )
     {
          for ( size_t i = 0; i < lhs.get_cols(); i++ )
          {
               for ( size_t j = 0; j < rhs.get_cols(); j++ )
               {
                    if ( ( pos + j ) % count == n )
                    {
                         result.get( pos, j ) += lhs.get( pos, i ) * rhs.get( i, j );
                    }
               }
          }
     }
}


void task_v2( const Matrix& lhs, const Matrix& rhs, Matrix& result, size_t n, size_t count )
{
     for ( size_t k = n; k < lhs.get_rows(); k += count )
     {
          for ( size_t i = 0; i < lhs.get_cols(); i++ )
          {
               for ( size_t j = 0; j < rhs.get_cols(); j++ )
               {
                    result.get( k, j ) += lhs.get( k, i ) * rhs.get( i, j );
               }
          }
     }
}


void strassen_step( Matrix& result, const Matrix& lhs, const Matrix& rhs, bool threaded = false )
{
     size_t n = lhs.get_rows() / 2;
     if ( n <= 8 )
     {
          result = lhs * rhs;
          return;
     }

     Matrix d{ n, n }, d1{ n, n }, d2{ n, n };
     Matrix h1{ n, n }, h2{ n, n };
     Matrix v1{ n, n }, v2{ n, n };

     MatrixSlice a11{ lhs, 0, 0, n, n };
     MatrixSlice a12{ lhs, 0, n, n, n };
     MatrixSlice a21{ lhs, n, 0, n, n };
     MatrixSlice a22{ lhs, n, n, n, n };

     MatrixSlice b11{ rhs, 0, 0, n, n };
     MatrixSlice b12{ rhs, 0, n, n, n };
     MatrixSlice b21{ rhs, n, 0, n, n };
     MatrixSlice b22{ rhs, n, n, n, n };

     if ( threaded )
     {
          std::thread t1( strassen_step, std::ref( d ) , a11 + a22, b11 + b22, false );
          std::thread t2( strassen_step, std::ref( d1 ), a12 - a22, b21 + b22, false );
          std::thread t3( strassen_step, std::ref( d2 ), a21 - a11, b11 + b12, false );
          std::thread t4( strassen_step, std::ref( h1 ), a11 + a12, b22, false );
          std::thread t5( strassen_step, std::ref( h2 ), a21 + a22, b11, false );
          std::thread t6( strassen_step, std::ref( v1 ), a22, b21 - b11, false );
          std::thread t7( strassen_step, std::ref( v2 ), a11, b12 - b22, false );
          t1.join();
          t2.join();
          t3.join();
          t4.join();
          t5.join();
          t6.join();
          t7.join();
     }
     else
     {
          strassen_step( d,  a11 + a22, b11 + b22 );
          strassen_step( d1, a12 - a22, b21 + b22 );
          strassen_step( d2, a21 - a11, b11 + b12 );
          strassen_step( h1, a11 + a12, b22 );
          strassen_step( h2, a21 + a22, b11 );
          strassen_step( v1, a22, b21 - b11 );
          strassen_step( v2, a11, b12 - b22 );
     }

     result.insert_part( d  + d1 + v1 - h1, 0, 0 );
     result.insert_part( v2 + h1, 0, n );
     result.insert_part( v1 + h2, n, 0 );
     result.insert_part( d  + d2 + v2 - h2, n, n );
}


template < typename Task >
Matrix multiply_matrices_parallel( const Matrix& lhs, const Matrix& rhs, size_t thread_count, Task task )
{
     if ( thread_count == 0 )
     {
          thread_count = defaultThreadCount;
     }
     Matrix result{ lhs.get_rows(), rhs.get_cols() };
     thread_count = std::min( thread_count, result.get_rows() );
     std::vector< std::thread > threads;
     threads.reserve( thread_count );

     for ( size_t i = 0; i < thread_count; i++ )
     {
          threads.emplace_back( task, std::cref( lhs ),
               std::cref( rhs ), std::ref( result ), i, thread_count );
     }
     for ( auto& thrd : threads )
     {
          thrd.join();
     }
     return result;
}

} // anonymous namespace


Matrix::Matrix( size_t rows, size_t cols ):
     rows_{ rows }, cols_{ cols }, data_( rows * cols, 0.0f )
{}


size_t Matrix::get_rows() const
{
     return rows_;
}


size_t Matrix::get_cols() const
{
     return cols_;
}


void Matrix::insert_part( const Matrix& matr, size_t row, size_t col )
{
     for ( size_t i = 0; i < matr.get_rows(); i++ )
     {
          for ( size_t j = 0; j < matr.get_cols(); j++ )
          {
               get( row + i, col + j ) = matr.get( i, j );
          }
     }
}


const float *Matrix::data() const
{
     return data_.data();
}


float *Matrix::data()
{
     return data_.data();
}


float Matrix::get( size_t i, size_t j ) const
{
     return data_[ i * cols_ + j ];
}


float& Matrix::get( size_t i, size_t j )
{
     return data_[ i * cols_ + j ];
}


Matrix operator*( const Matrix& lhs, const Matrix& rhs )
{
     assert( lhs.get_cols() );
     assert( rhs.get_cols() );
     assert( lhs.get_cols() == rhs.get_rows() );
     Matrix result( lhs.get_rows(), rhs.get_cols() );
     for ( size_t i = 0; i < result.get_rows(); i++ )
     {
          for ( size_t j = 0; j < result.get_cols(); j++ )
          {
               for ( size_t k = 0; k < lhs.get_cols(); k++ )
               {
                    result.get( i, j ) += lhs.get( i, k ) * rhs.get( k, j );
               }
          }
     }
     return result;
}


bool operator==( const Matrix& lhs, const Matrix& rhs )
{
     if ( lhs.rows_ != rhs.rows_ || lhs.cols_ != rhs.cols_ )
     {
          return false;
     }
     for ( size_t i = 0; i < lhs.data_.size(); i++ )
     {
          if ( std::fabs( lhs.data_[ i ] - rhs.data_[ i ] ) > Matrix::compare_precision )
          {
               return false;
          }
     }
     return true;
}


Matrix Matrix::generate( size_t i, size_t j )
{
     assert( i );
     assert( j );
     Matrix result( i, j );
     size_t elem_count = i * j;
     for ( size_t k = 0; k < elem_count; k++ )
     {
          result.data_[ k ] = rand_min + std::rand() / ( RAND_MAX / ( rand_max - rand_min ) );
     }
     return result;
}


std::ostream& operator<<( std::ostream& lhs, const Matrix& rhs )
{
     for ( size_t i = 0; i < rhs.get_rows(); i++ )
     {
          for ( size_t j = 0; j < rhs.get_cols(); j++ )
          {
               lhs << std::setprecision( Matrix::output_precision ) << std::fixed
                   << std::setw( 10 ) << rhs.get( i, j );
          }
          lhs << '\n';
     }
     return lhs;
}


Matrix multiply_matrices_strassen( const Matrix& lhs, const Matrix& rhs )
{
     Matrix result{ lhs.get_rows(), rhs.get_cols() };
     strassen_step( result, lhs, rhs, true );
     return result;
}


Matrix multiply_matrices_parallel_v1( const Matrix& lhs, const Matrix& rhs, size_t thread_count )
{
     return multiply_matrices_parallel( lhs, rhs, thread_count, task_v1 );
}


Matrix multiply_matrices_parallel_v2( const Matrix& lhs, const Matrix& rhs, size_t thread_count )
{
     return multiply_matrices_parallel( lhs, rhs, thread_count, task_v2 );
}
