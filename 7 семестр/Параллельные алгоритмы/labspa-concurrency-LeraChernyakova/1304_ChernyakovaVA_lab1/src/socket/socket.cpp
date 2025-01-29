#include "socket.h"

#include <cstring>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdexcept>

Socket::Socket(int fileDescriptor) : fileDescriptor_{fileDescriptor} {}

Socket::Socket(const std::string& fileName) : fileDescriptor_{-1} {
    struct sockaddr_un address;
    fileDescriptor_ = ::socket(AF_UNIX, SOCK_SEQPACKET, 0);

    if (fileDescriptor_ == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    std::memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    std::strncpy(address.sun_path, fileName.c_str(), sizeof(address.sun_path) - 1);

    while (::connect(fileDescriptor_, (const struct sockaddr*)&address, sizeof(address)) == -1) {}
}

Socket::Socket(Socket&& other): fileDescriptor_{other.fileDescriptor_} {
    other.fileDescriptor_ = -1;
}

Socket::~Socket() {
    if (isValid()) {
        ::close(fileDescriptor_);
    }
}

bool Socket::isValid() const {
    return fileDescriptor_ != -1;
}

bool Socket::writeData(const int* data, int dataSize) const {
    const ssize_t size = dataSize * sizeof(int);
    return size == ::write(fileDescriptor_, data, size);
}

bool Socket::readData(int* data, int dataSize) const {
    const ssize_t size = dataSize * sizeof(int);
    return size == ::read(fileDescriptor_, data, size);
}
