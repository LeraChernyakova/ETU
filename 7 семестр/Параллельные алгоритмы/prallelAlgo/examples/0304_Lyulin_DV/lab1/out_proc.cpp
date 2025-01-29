#include <iostream>
#include <cstdlib>

#include <unix_socket.h>
#include <common.h>
#include <matrix.h>


int main()
{
     UnixSocket socket( outdata_socket );
     if ( !make_client( socket ) )
     {
          return EXIT_FAILURE;
     }
     Matrix matr;
     if ( !read_matrix( socket, matr ) )
     {
          return EXIT_FAILURE;
     }
     std::cout << "RESULT:\n" << matr << '\n';
     return EXIT_SUCCESS;
}
