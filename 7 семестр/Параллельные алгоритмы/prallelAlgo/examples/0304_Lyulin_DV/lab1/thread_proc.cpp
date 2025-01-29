#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>

#include <unix_socket.h>
#include <common.h>
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


void calculate( const Matrix& lhs, const Matrix& rhs, Matrix& result )
{
     calc_sync.wait();
     result = lhs * rhs;
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
     if ( !read_sizes( argc, argv, sizes ) )
     {
          return EXIT_FAILURE;
     }
     std::srand( std::time( nullptr ) );
     Matrix lhs, rhs, result;

     // thread 1
     std::thread in_thread( input, std::ref( lhs ), std::ref( rhs ), sizes );
     // thread 2
     std::thread calc_thread( calculate, std::cref( lhs ), std::cref( rhs ), std::ref( result ) );
     // thread 3
     std::thread out_thread( output, std::cref( lhs ), std::cref( rhs ), std::cref( result ) );

     in_sync.notify();

     in_thread.join();
     calc_thread.join();
     out_thread.join();

     return EXIT_SUCCESS;
}
