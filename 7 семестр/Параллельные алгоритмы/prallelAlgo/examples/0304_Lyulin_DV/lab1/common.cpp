#include <common.h>

#include <iostream>
#include <iomanip>

#include <unix_socket.h>
#include <matrix.h>
#include <utils.h>


bool read_sizes( int argc, char *argv[], size_t *sizes )
{
     if ( argc < 5 )
     {
          std::cerr << "Usage: " << argv[ 0 ] << " m1_rows m1_cols m2_rows m2_cols\n";
          return false;
     }
     for ( size_t i = 0; i < 4; i++ )
     {
          if ( !str_to_size( argv[ i + 1 ], sizes[ i ] ) )
          {
               std::cerr << "Cannot convert '" << argv[ i + 1 ] << "' to size_t\n";
               return false;
          }
     }
     if ( sizes[ 1 ] != sizes[ 2 ] )
     {
          std::cerr << "Wrong matrix sizes\n";
          return false;
     }
     return true;
}


bool make_server( UnixSocket& socket )
{
     if ( !socket.is_valid() )
     {
          std::cerr << "Error: Cannot create socket\n";
          return false;
     }
     if ( !socket.setup_server() )
     {
          std::cerr << "Error: Cannot setup server\n";
          return false;
     }
     return true;
}


bool make_client( UnixSocket& socket )
{
     if ( !socket.is_valid() )
     {
          std::cerr << "Error: Cannot create socket\n";
          return false;
     }
     while ( !socket.setup_client() );
     return true;
}


bool read_matrix( Socket& socket, Matrix& matr )
{
     size_t sizes[ 2 ];
     if ( !socket.read( &sizes[ 0 ], 2 ) )
     {
          std::cerr << "Error: Cannot read matrix sizes\n";
          return false;
     }

     Matrix ret{ sizes[ 0 ], sizes[ 1 ] };
     if ( !socket.read( ret.data(), sizes[ 0 ] * sizes[ 1 ] ) )
     {
          std::cerr << "Error: Cannot read matrix data\n";
          return false;
     }
     matr = ret;
     return true;
}


bool write_matrix( Socket& socket, const Matrix& matr )
{
     size_t sizes[ 2 ] = { matr.get_rows(), matr.get_cols() };
     if ( !socket.write( &sizes[ 0 ], 2 ) )
     {
          std::cerr << "Error: Cannot write matrix sizes\n";
          return false;
     }
     if ( !socket.write( matr.data(), sizes[ 0 ] * sizes[ 1 ] ) )
     {
          std::cerr << "Error: Cannot write matrix data\n";
          return false;
     }
     return true;
}
