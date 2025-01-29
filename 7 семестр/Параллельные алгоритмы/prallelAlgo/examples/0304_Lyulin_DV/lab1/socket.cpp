#include <socket.h>

#include <utility>

#include <sys/socket.h>

Socket::Socket( int sockfd ) : sockfd_{ sockfd } {}


Socket::Socket() : sockfd_{ -1 } {}


Socket::Socket( Socket&& other ) : sockfd_{ -1 }
{
     std::swap( sockfd_, other.sockfd_ );
}


Socket::~Socket()
{
     if ( is_valid() )
     {
          ::close( sockfd_ );
     }
}


Socket& Socket::operator=( Socket&& rhs )
{
     if ( this != &rhs )
     {
          std::swap( sockfd_, rhs.sockfd_ );
     }
     return *this;
}


bool Socket::is_valid() const
{
     return sockfd_ != -1;
}
