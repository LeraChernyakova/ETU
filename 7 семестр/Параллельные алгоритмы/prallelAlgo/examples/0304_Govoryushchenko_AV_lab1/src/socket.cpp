#include "./socket.h"
#include <cstring>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>

Socket::Socket(int fd) : _fd{fd} {}

Socket::Socket(const std::string& fileName): _fd{-1} {
    struct sockaddr_un addr;
    _fd = ::socket(AF_UNIX, SOCK_SEQPACKET, 0); // Create local socket
    std::memset(&addr, 0, sizeof(addr)); // Clear whole structure for portability
    addr.sun_family = AF_UNIX; // Bind socket to socket addr
    std::strncpy(addr.sun_path, fileName.c_str(), sizeof(addr.sun_path) - 1);
    while (-1 == ::connect(_fd, (const struct sockaddr *) &addr, sizeof(addr))); 
    // {
    //     ::close(_fd);
    //     _fd = -1;
    // }
}

Socket::Socket(Socket&& other) {
    _fd = other._fd;
    other._fd = -1;
}

Socket::~Socket() {
    if (valid()) {
        ::close(_fd);
    }
}

bool Socket::valid() const {
    return _fd != -1;
}

bool Socket::write(const int *data, int count) const {
    int size = count * sizeof(int);
    return size == ::write(_fd, data, size);
}

bool Socket::read(int *data, int count) const {
    int size = count * sizeof(int);
    return size == ::read(_fd, data, size);
}
