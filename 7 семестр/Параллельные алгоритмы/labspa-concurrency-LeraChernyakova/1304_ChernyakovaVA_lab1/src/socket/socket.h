#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class Socket {
protected:
int fileDescriptor_;

public:
    Socket(int fileDescriptor = -1);
    Socket(const std::string& fileName);

    Socket(Socket&& other);

    virtual ~Socket();

    bool isValid() const;
    bool writeData(const int* data, int dataSize) const;
    bool readData(int* data, int dataSize) const;
};

#endif //SOCKET_H
