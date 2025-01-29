#include "../matrix/matrix.h"
#include "../socket/server_socket.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

int main(int argc, char *argv[]) {
    try {
        int leftRows, leftCols, rightRows, rightCols;
        if (!readRowsCols(argc, argv, leftRows, leftCols, rightRows, rightCols)) {
            throw std::runtime_error("Write: " + std::string(argv[0])
                    + " left_matrix_rows left_matrix_cols right_matrix_rows right_matrix_cols ");
        }
        if (leftCols != rightRows) {
            throw std::invalid_argument("Error: Matrix dimensions do not match for multiplication");
        }

        std::srand(std::time(nullptr));
        Matrix leftMatrix = createMatrix(leftRows, leftCols);
        Matrix rightMatrix = createMatrix(rightRows, rightCols);

        ServerSocket server_reader(readerSocket);
        if (!server_reader.isValid()) {
            throw std::runtime_error("Error: Cannot create server socket");
        }

        Socket client_reader = server_reader.acceptConnection();
        if (!client_reader.isValid()) {
            throw std::runtime_error("Error: Cannot create client socket");
        }

        if (!sendMatrix(client_reader, leftMatrix) || !sendMatrix(client_reader, rightMatrix)) {
            throw std::runtime_error("Error: Failed to send matrix data");
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
