#ifndef SOCKET_H
#define SOCKET_H

#include <cstdint>
#include <unistd.h>
#include <iostream>

/// @brief RAII socket wrapper.
class Socket
{
public:
     explicit Socket( int sockfd );
     Socket( Socket&& other );
     Socket();
     virtual ~Socket();

     Socket& operator=( Socket&& rhs );

     Socket( const Socket& )            = delete;
     Socket& operator=( const Socket& ) = delete;

     bool is_valid() const;

     template < typename T >
     bool read( T* buffer, std::size_t nmemb )
     {
          std::size_t bytes_size = nmemb * sizeof( T );
          return bytes_size == ::read( sockfd_, buffer, bytes_size );
     }

     template < typename T >
     bool write( const T* buffer, std::size_t nmemb )
     {
          std::size_t bytes_size = nmemb * sizeof( T );
          return bytes_size == ::write( sockfd_, buffer, bytes_size );
     }

protected:
     int sockfd_;
};

#endif // SOCKET_H