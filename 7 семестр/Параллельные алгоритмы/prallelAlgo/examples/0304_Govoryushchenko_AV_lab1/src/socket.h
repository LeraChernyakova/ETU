#pragma once
#include <string>

class Socket {
    public:
        Socket(int fd = -1);
        Socket(const std::string& fileName);
        Socket(Socket&& other);
        virtual ~Socket();

        bool valid() const;
        bool write(const int *data, int count) const;
        bool read(int *data, int count) const;
    
    protected:
        int _fd;
};
