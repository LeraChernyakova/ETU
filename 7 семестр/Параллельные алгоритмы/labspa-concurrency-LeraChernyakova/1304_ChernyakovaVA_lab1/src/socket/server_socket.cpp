#include "server_socket.h"

#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

ServerSocket::ServerSocket(const std::string& fileName) : Socket(-1) {
    ::unlink(fileName.c_str());
    fileDescriptor_ = ::socket(AF_UNIX, SOCK_SEQPACKET, 0);

    if (fileDescriptor_ == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    std::memset(&address_, 0, sizeof(address_));
    address_.sun_family = AF_UNIX;
    std::strncpy(address_.sun_path, fileName.c_str(), sizeof(address_.sun_path) - 1);

    if (::bind(fileDescriptor_, (const struct sockaddr*)&address_, sizeof(address_)) == -1) {
        ::close(fileDescriptor_);
        fileDescriptor_ = -1;
        throw std::runtime_error("Failed to bind socket");
    }

    if (::listen(fileDescriptor_, 1) == -1) {
        ::close(fileDescriptor_);
        fileDescriptor_ = -1;
        throw std::runtime_error("Failed to listen on socket");
    }
}

ServerSocket::~ServerSocket() {
    ::unlink(address_.sun_path);
}

Socket ServerSocket::acceptConnection() {
    int clientSocket = ::accept(fileDescriptor_, nullptr, nullptr);
    if (clientSocket == -1) {
        throw std::runtime_error("Failed to accept connection");
    }
    return Socket(clientSocket);
}
