#include "../matrix/matrix.h"
#include "../socket/server_socket.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Matrix leftMatrix, rightMatrix;

        ServerSocket server_writer(writerSocket);
        if (!server_writer.isValid()) {
            throw std::runtime_error("Error: Failed to create server socket");
        }

        Socket client_reader(readerSocket);
        if (!client_reader.isValid()) {
            throw std::runtime_error("Error: Failed to create client socket");
        }

        if (!readMatrix(client_reader, leftMatrix) || !readMatrix(client_reader, rightMatrix)) {
            throw std::runtime_error("Error: Failed to read matrices");
        }

        printMatrix(leftMatrix, "left_matrix");
        printMatrix(rightMatrix, "right_matrix");

        Socket client_writer = server_writer.acceptConnection();
        if (!client_writer.isValid()) {
            throw std::runtime_error("Error: Failed to create data socket");
        }

        Matrix resultMatrix = leftMatrix * rightMatrix;
        if (!sendMatrix(client_writer, resultMatrix)) {
            throw std::runtime_error("Error: Failed to send result matrix");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}