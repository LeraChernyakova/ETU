#include <iostream>
#include <cstdlib>

#include <unix_socket.h>
#include <matrix.h>
#include <common.h>

int main()
{
     UnixSocket in_socket( indata_socket );
     if ( !make_client( in_socket ) )
     {
          return EXIT_FAILURE;
     }
     Matrix matr[ 2 ];
     for ( size_t i = 0; i < 2; i++ )
     {
          if ( !read_matrix( in_socket, matr[ i ] ) )
          {
               return EXIT_FAILURE;
          }
          std::cout << "GOT MATRIX:\n" << matr[ i ] << '\n';
     }
     Matrix out_matr{ matr[ 0 ] * matr[ 1 ] };
     UnixSocket out_socket( outdata_socket );
     if ( !make_server( out_socket ) )
     {
          return EXIT_FAILURE;
     }
     Socket data_socket = out_socket.accept_connection();
     if ( !write_matrix( data_socket, out_matr ) )
     {
          return EXIT_FAILURE;
     }
     return EXIT_SUCCESS;
}
