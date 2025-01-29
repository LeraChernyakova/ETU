#include <iostream>
#include <cstdlib>
#include <ctime>
#include "./matrix.h"
#include "./common.h"
#include "./serverSocket.h"

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    int rows1, cols1, rows2, cols2;
    if (!readMatrices(argc, argv, rows1, cols1, rows2, cols2))
    {
        std::cout << "Usage: " << argv[0] << " m1_rows m1_cols m2_rows m2_cols\n";
        return 1;
    }
    if (cols1 != rows2) {
        std::cout << "Wrong matrix sizes\n";
        return 1;
    }
    Matrix m1 = createMatrix(rows1, cols1);
    Matrix m2 = createMatrix(rows2, cols2);
    ServerSocket server(readerSocket);
    if (!server.valid()) {
        std::cout << "Cannot create socket\n";
        return 1;
    }
    Socket dataSocket = server.accept(); // socket for incoming connections
    if (!dataSocket.valid()) {
        std::cout << "Cannot create data socket\n";
        return 1;
    }
    if (!sendMatrix(dataSocket, m1) || !sendMatrix(dataSocket, m2)) {
        return 1;
    }
    return 0;
}
