#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cassert>
#include <functional>
#include <iostream>

#include <utils.h>
#include <matrix.h>


namespace
{

inline constexpr bool is_power_of_2( size_t x )
{
     return 0 == ( x & ( x - 1 ) );
}


double measure_time( const std::function< void() >& oper )
{
     auto t1 = std::chrono::high_resolution_clock::now();
     oper();
     auto t2 = std::chrono::high_resolution_clock::now();
     return std::chrono::duration< double, std::milli >( t2 - t1 ).count();
}

} // namespace


int main( int argc, char *argv[] )
{
     size_t matrix_size;
     
     if ( argc != 2 || !str_to_size( argv[ 1 ], matrix_size )
       || matrix_size == 0 || !is_power_of_2( matrix_size ) )
     {
          std::cerr << "Usage: " << argv[ 0 ] << " <matrix_size (power of 2)>\n";
          return EXIT_FAILURE;
     }
     std::srand( std::time( nullptr ) );
     Matrix lhs{ Matrix::generate( matrix_size, matrix_size ) };
     Matrix rhs{ Matrix::generate( matrix_size, matrix_size ) };
     Matrix result1, result2, result3, result4;

     double time1 = measure_time( [ &lhs, &rhs, &result1 ](){ result1 = multiply_matrices_parallel_v1( lhs, rhs ); } );
     double time2 = measure_time( [ &lhs, &rhs, &result2 ](){ result2 = multiply_matrices_parallel_v2( lhs, rhs ); } );
     double time3 = measure_time( [ &lhs, &rhs, &result3 ](){ result3 = multiply_matrices_strassen( lhs, rhs ); } );
     double time4 = measure_time( [ &lhs, &rhs, &result4 ](){ result4 = lhs * rhs; } );

     std::cout << "Threads v1: " << time1 << " ms\n"
               << "Threads v2: " << time2 << " ms\n"
               << "Strassen  : " << time3 << " ms\n"
               << "Simple    : " << time4 << " ms\n";

     return EXIT_SUCCESS;
}
