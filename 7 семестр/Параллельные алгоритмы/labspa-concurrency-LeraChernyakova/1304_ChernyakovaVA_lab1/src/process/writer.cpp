#include "../matrix/matrix.h"
#include "../socket/server_socket.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Matrix resultMatrix;
        Socket client_writer(writerSocket);

        if (!client_writer.isValid()) {
            throw std::runtime_error("Error: Failed to create server socket");
        }

        if (!readMatrix(client_writer, resultMatrix)) {
            throw std::runtime_error("Error: Failed to read matrix");
        }

        printMatrix(resultMatrix, "result_matrix");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
