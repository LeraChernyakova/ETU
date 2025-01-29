#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include <string>

#include <sys/un.h>

#include <socket.h>

/// @brief Unix domain socket for IPC.
class UnixSocket : public Socket
{
public:
     explicit UnixSocket( const std::string& sock_file );

     ~UnixSocket();

     bool setup_server( size_t queue_size = 1 );
     bool setup_client();
     Socket accept_connection();

private:
     struct sockaddr_un sockaddr_;
     bool is_server_;
};

#endif // UNIX_SOCKET_H
