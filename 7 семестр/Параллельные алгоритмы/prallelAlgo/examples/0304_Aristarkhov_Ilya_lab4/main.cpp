#include <iostream>
#include "./model/Square_matrix.h"
#include "./thread/Matrix_threading.h"

#define DEBUG


int main(int args, char** argv) {

#ifdef DEBUG
    int matrix_size {32};
#else
    if (args != 2) {
        std::exit(-1);
    }

    int matrix_size {std::stoi(argv[1])};
#endif

    int threads_count {matrix_size};

    Square_matrix matrix1(matrix_size);
    Square_matrix matrix2(matrix_size);

    Square_matrix concurrent_result(matrix_size);
    Square_matrix strassen_result(matrix_size);

    Matrix_threading::generate(matrix1, matrix2, matrix_size);

//    Matrix_threading::output("./matrix1.txt", matrix1);
//    Matrix_threading::output("./matrix2.txt", matrix2);


    auto start = std::chrono::high_resolution_clock::now();

    Matrix_threading::concurrent_multiply(concurrent_result, threads_count, matrix1, matrix2);

    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << duration.count() << std::endl;


    start = std::chrono::high_resolution_clock::now();

    Matrix_threading::strassen_multiply(strassen_result, matrix1, matrix2);

    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << duration.count() << std::endl;

//    Matrix_threading::output("./concurrent_result.txt", concurrent_result);
//    Matrix_threading::output("./strassen_result.txt", strassen_result);

#ifdef DEBUG
    if (concurrent_result == strassen_result) {
        std::cout << "Results of multiplication are the same!" << std::endl;
    } else {
        std::cout << "Results of multiplication are NOT the same!" << std::endl;
    }
#endif

    return 0;
}
