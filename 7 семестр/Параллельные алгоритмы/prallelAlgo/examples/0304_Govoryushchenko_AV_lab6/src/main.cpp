#include <cstdlib>
#include <iostream>
#include <memory>
#include <ctime>
#include <chrono>

#include <matrix.h>
#include <matrixOCL.h>


bool str_to_size(const std::string& str, std::size_t& num)
{
    try
    {
        num = std::stoul(str);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
 
int main(int argc, char *argv[]) {
    size_t matrixSize;
    if (argc != 2 || !str_to_size(argv[1], matrixSize) || matrixSize % workgroupSize[0])
    {
        std::cout << "Usage: " << argv[0] << " <matrixSize>\n";
        return EXIT_FAILURE;
    }

    std::srand(std::time(nullptr));
    Matrix lhs{createMatrix(matrixSize, matrixSize)};
    Matrix rhs{createMatrix(matrixSize, matrixSize)};
    auto t1 = std::chrono::high_resolution_clock::now();
    Matrix result = multiplyMatricesOcl(lhs, rhs);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration< double, std::milli >(t2 - t1).count() << " ms\n";

    exit(EXIT_SUCCESS);
}