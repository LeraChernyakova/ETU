#include <iostream>
#include "./matrix.h"
#include "./common.h"
#include "./serverSocket.h"

int main(int argc, char *argv[]) {
    Matrix m1, m2;
    ServerSocket server(executorSocket);
    if (!server.valid()) {
        std::cout << "Cannot create socket\n";
        return 1;
    }
    Socket socket(readerSocket);
    if (!socket.valid()) {
        std::cout << "Cannot create socket\n";
        return 1;
    }
    if (!receiveMatrix(socket, m1) || !receiveMatrix(socket, m2)) {
        return 1;
    }
    std::cout << "RECEIVED MATRIX:\n";
    printMatrix(m1);
    std::cout << "RECEIVED MATRIX:\n";
    printMatrix(m2);

    Socket dataSocket = server.accept();
    if (!dataSocket.valid()) {
        std::cout << "Cannot create data socket\n";
        return 1;
    }
    if (!sendMatrix(dataSocket, m1 * m2)) {
        return 1;
    }
    return 0;
}
