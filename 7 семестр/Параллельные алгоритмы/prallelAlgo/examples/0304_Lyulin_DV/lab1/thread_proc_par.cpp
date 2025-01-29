#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <cstdlib>
#include <ctime>

#include <unix_socket.h>
#include <common.h>
#include <utils.h>
#include <matrix.h>
#include <thread_sync.h>

namespace
{

ThreadSync in_sync;
ThreadSync calc_sync;
ThreadSync out_sync;

} // anonymous namespace


void input( Matrix& lhs, Matrix& rhs, size_t *sizes )
{
     in_sync.wait();

     lhs = Matrix::generate( sizes[ 0 ], sizes[ 1 ] );
     rhs = Matrix::generate( sizes[ 2 ], sizes[ 3 ] );
     std::cout << "GOT MATRIX:\n" << lhs << '\n';
     std::cout << "GOT MATRIX:\n" << rhs << '\n';

     calc_sync.notify();
}


void calculate( size_t thread_count, const Matrix& lhs, const Matrix& rhs, Matrix& result )
{
     calc_sync.wait();

     result = multiply_matrices_parallel_v1( lhs, rhs, thread_count );

     out_sync.notify();
}


void output( const Matrix& lhs, const Matrix& rhs, const Matrix& result )
{
     out_sync.wait();
     std::cout << "RESULT:\n" << result << '\n';
}


int main( int argc, char *argv[] )
{
     size_t sizes[ 4 ];
     size_t thread_count;
     if ( !read_sizes( argc, argv, sizes ) )
     {
          return EXIT_FAILURE;
     }
     if ( argc > 5 && !str_to_size( argv[ 5 ], thread_count ) )
     {
          std::cerr << "Cannot read number of calculation threads (P)\n";
          return EXIT_FAILURE;
     }
     std::srand( std::time( nullptr ) );
     Matrix lhs, rhs, result;

     // thread 1
     std::thread in_thread( std::bind( input, std::ref( lhs ), std::ref( rhs ), sizes ) );
     // thread 2
     std::thread calc_thread( std::bind( calculate, thread_count, std::cref( lhs ), std::cref( rhs ), std::ref( result ) ) );
     // thread 3
     std::thread out_thread( std::bind( output, std::cref( lhs ), std::cref( rhs ), std::cref( result ) ) );

     in_sync.notify();

     in_thread.join();
     calc_thread.join();
     out_thread.join();

     return EXIT_SUCCESS;
}
