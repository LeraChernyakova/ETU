#include <cstdlib>
#include <ctime>

#include <unix_socket.h>
#include <common.h>
#include <matrix.h>


int main( int argc, char *argv[] )
{
     size_t sizes[ 4 ];
     if ( !read_sizes( argc, argv, sizes ) )
     {
          return EXIT_FAILURE;
     }
     std::srand( std::time( nullptr ) );
     UnixSocket in_socket( indata_socket );
     if ( !make_server( in_socket ) )
     {
          return EXIT_FAILURE;
     }
     Socket data_socket = in_socket.accept_connection();
     for ( size_t i = 0; i < 2; i++ )
     {
          Matrix matr{ Matrix::generate( sizes[ i * 2 ], sizes[ i * 2 + 1 ] ) };
          if ( !write_matrix( data_socket, matr ) )
          {
               return EXIT_FAILURE;
          }
     }
     return EXIT_SUCCESS;
}
