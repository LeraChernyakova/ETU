#include <iostream>
#include "./matrix.h"
#include "./common.h"
#include "./serverSocket.h"

int main(int argc, char *argv[]) {
    Matrix m;
    Socket socket(executorSocket);
    if (!socket.valid()) {
        std::cout << "Cannot create socket\n";
        return 1;
    }
    if (!receiveMatrix(socket, m)) {
        return 1;
    }
    std::cout << "RESULT MATRIX:\n";
    printMatrix(m);
    return 0;
}
