#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "socket.h"

#include <sys/un.h>
#include <stdexcept>

class ServerSocket : public Socket {
private:
    struct sockaddr_un address_;

public:
    ServerSocket(const std::string& fileName);
    ~ServerSocket();

    Socket acceptConnection();
};

#endif // SERVER_SOCKET_H
