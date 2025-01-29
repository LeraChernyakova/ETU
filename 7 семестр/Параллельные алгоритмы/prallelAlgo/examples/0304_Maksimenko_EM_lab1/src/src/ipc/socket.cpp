#include "ipc/socket.h"

ipc::Socket::Socket( const int fd ) noexcept
    : fd_{ fd }
{
    if ( -1 == fd_ )
    {
        isValid_ = false;
    }
} // Socket


ipc::Socket::~Socket()
{
    close();
} // ~Socket


void ipc::Socket::close()
{
    if ( isValid() )
    {
        ::close( fd_ );
        ::shutdown( fd_, SHUT_RDWR );
    }
} // close
