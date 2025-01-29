#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include "engine/Open_cl_engine.h"
#include "strassen/model/Square_matrix.h"
#include "strassen/thread/Matrix_threading.h"


auto main() -> int {

    const size_t size = 2048;

    Open_cl_engine engine{};

    // Getting device, creating context and command queue
    engine.init();

    // Reading .cl source code
    std::ifstream f("../matrix_multiply.cl");
    std::stringstream buf;
    buf << f.rdbuf();
    std::string source_code{buf.str()};

    // Building program and creating kernel for it
    engine.load_program(source_code, "matrix_multiply");

    auto start = std::chrono::high_resolution_clock::now();

    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution die100{-100, 100};

    Square_matrix matrix1(size);
    Square_matrix matrix2(size);
    Square_matrix strassen_result(size);


    std::vector<int> first_buffer_data(size * size);
    std::vector<int> second_buffer_data(size * size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int firstData = die100(mt);
            int secondData = die100(mt);
            first_buffer_data[i * size + j] = firstData;
            matrix1.set_data(firstData, i, j);

            second_buffer_data[i * size + j] = secondData;
            matrix2.set_data(secondData, i, j);
        }
    }

    // Creating img argument for program and loading it into the kernel
    // Also enqueuing kernel work??
    engine.create_buffers(size, first_buffer_data, second_buffer_data);

    engine.execute_and_wait();
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << duration.count() << '\n';

    // Creating var for image read and creating read task in queue
    int *resultMatrix = new int[size * size];
    engine.read_buffer(resultMatrix, size);

    // Flushing queue and wait for completion
    engine.execute_and_wait();


//    Matrix_threading::strassen_multiply(strassen_result, matrix1, matrix2);
//
//    bool same = true;
//
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            if (strassen_result.get_data(i, j) != resultMatrix[i * size + j]) {
//                same = false;
//                std::cout << "Results of multiplication are NOT the same!" << std::endl;
//                break;
//            }
//        }
//        if (!same) {
//            break;
//        }
//    }
//
//    if (same) {
//        std::cout << "Results of multiplication are the same!" << std::endl;
//    } else {
//        for (int i = 0; i < size; ++i) {
//            for (int j = 0; j < size; ++j) {
//                std::cout << resultMatrix[i * size + j];
//                std::cout << " ";
//            }
//            std::cout << "\n";
//        }
//
//        std::cout << "\n";
//        std::cout << "\n";
//
//        for (int i = 0; i < size; ++i) {
//            for (int j = 0; j < size; ++j) {
//                std::cout << strassen_result.get_data(i, j);
//                std::cout << " ";
//            }
//            std::cout << "\n";
//        }
//    }

    // Cleaning up (closing kernel, program, img_variable, queue and context)
    engine.clean_up();
    // Removing image byte array
    delete[] resultMatrix;
}
