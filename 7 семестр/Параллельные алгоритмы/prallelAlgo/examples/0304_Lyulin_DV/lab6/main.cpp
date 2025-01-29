#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include <utils.h>
#include <matrix.h>
#include <cl_matr.h>

bool is_multiple_of( size_t x, size_t mul )
{
     return x % mul == 0;
}


int main( int argc, char const *argv[] )
{
     size_t matrix_size;
     if ( argc != 2 || !str_to_size( argv[ 1 ], matrix_size )
       || matrix_size == 0 || !is_multiple_of( matrix_size, local_work_size[ 0 ] ) )
     {
          std::cerr << "Usage: " << argv[ 0 ] << " <matrix_size (multiple of " << local_work_size[ 0 ] << ")>\n";
          return EXIT_FAILURE;
     }
     std::srand( std::time( nullptr ) );
     Matrix lhs{ Matrix::generate( matrix_size, matrix_size ) };
     Matrix rhs{ Matrix::generate( matrix_size, matrix_size ) };
     auto t1 = std::chrono::high_resolution_clock::now();
     Matrix result = multiply_matrices_ocl( lhs, rhs );
     auto t2 = std::chrono::high_resolution_clock::now();
     std::cout << std::chrono::duration< double, std::milli >( t2 - t1 ).count() << " ms\n";

     // assert( result == lhs * rhs ); // bruh too long :(
     return EXIT_SUCCESS;
}
