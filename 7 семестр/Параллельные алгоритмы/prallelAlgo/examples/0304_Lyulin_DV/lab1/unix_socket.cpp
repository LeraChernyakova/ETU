#include <unix_socket.h>

#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

UnixSocket::UnixSocket( const std::string& sock_file ):
     Socket::Socket{ ::socket( AF_UNIX, SOCK_STREAM, 0 ) }, is_server_{ false }
{
     std::memset( &sockaddr_, 0, sizeof( sockaddr_ ) );
     sockaddr_.sun_family = AF_UNIX;
     strncpy( sockaddr_.sun_path, sock_file.c_str(), sizeof( sockaddr_.sun_path ) - 1 );
}


UnixSocket::~UnixSocket()
{
     if ( is_server_ )
     {
          ::unlink( sockaddr_.sun_path );
     }
}


bool UnixSocket::setup_server( size_t queue_size )
{
     ::unlink( sockaddr_.sun_path );
     if ( ::bind( sockfd_, reinterpret_cast< const struct sockaddr* >( &sockaddr_ ),
          sizeof( sockaddr_ ) ) )
     {
          return false;
     }
     is_server_ = true;
     if ( ::listen( sockfd_, queue_size ) )
     {
          return false;
     }
     return true;
}


bool UnixSocket::setup_client()
{
     return ::connect( sockfd_, reinterpret_cast< const struct sockaddr* >( &sockaddr_ ),
                   sizeof( sockaddr_ ) ) == 0;
}


Socket UnixSocket::accept_connection()
{
     return Socket{ ::accept( sockfd_, nullptr, nullptr ) };
}
