#include "./serverSocket.h"
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

ServerSocket::ServerSocket(const std::string fileName)
    : Socket::Socket(-1)
{
    ::unlink(fileName.c_str());
    _fd = ::socket(AF_UNIX, SOCK_SEQPACKET, 0);
    std::memset(&_addr, 0, sizeof(_addr));
    _addr.sun_family = AF_UNIX;
    std::strncpy(_addr.sun_path, fileName.c_str(), sizeof(_addr.sun_path) - 1);
    if (::bind(_fd, (const struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        ::close(_fd);
        _fd = -1;
    }
    if (::listen(_fd, 1) == -1) {
        ::close(_fd);
        _fd = -1;
    }
}

ServerSocket::~ServerSocket() {
    ::unlink(_addr.sun_path);
}

Socket ServerSocket::accept() {
    return Socket(::accept(_fd, nullptr, nullptr));
}
