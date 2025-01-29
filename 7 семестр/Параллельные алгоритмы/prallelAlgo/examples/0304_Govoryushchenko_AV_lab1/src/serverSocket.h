#include "./socket.h"
#include <sys/un.h>

class ServerSocket: public Socket  {
    public:
        ServerSocket(const std::string fileName);
        ~ServerSocket();
    
        Socket accept();

    private:
        struct sockaddr_un _addr;
};
