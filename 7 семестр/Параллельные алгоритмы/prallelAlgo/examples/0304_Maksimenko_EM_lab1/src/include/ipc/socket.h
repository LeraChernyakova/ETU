#ifndef IPC_SOCKET_H
#define IPC_SOCKET_H

#include <string>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace ipc
{

class Socket
{
public:
    Socket( const int fd ) noexcept;
    virtual ~Socket();

    inline bool isValid() const { return isValid_; }
    inline const std::string& getErrMsg() const { return errMsg_; }

    template< typename T >
    ssize_t read( T* buffer, const size_t countElements = 1 )
    {
        if ( !isValid() )
        {
            errMsg_ = "Socket is invalid";
            return -1;
        }

        const size_t bufferSize = sizeof( T ) * countElements;
        return ::recv( fd_, reinterpret_cast< void* >( buffer ), bufferSize, 0 );
    }

    template< typename T >
    ssize_t write( T* buffer, const size_t countElements = 1 )
    {
        if ( !isValid() )
        {
            errMsg_ = "Socket is invalid";
            return -1;
        }

        const size_t bufferSize = sizeof( T ) * countElements;
        return ::send( fd_, reinterpret_cast< const void* >( buffer ), bufferSize, MSG_NOSIGNAL );
    }

    virtual void close();

protected:
    int fd_;                            ///< Файловый дескриптор сокета.
    bool isValid_ = true;               ///< Валидность сокета и соединения.
    std::string errMsg_;                ///< Сообщение об ошибке.

}; // class Socket

} // namespace ipc

#endif // IPC_SOCKET_H
