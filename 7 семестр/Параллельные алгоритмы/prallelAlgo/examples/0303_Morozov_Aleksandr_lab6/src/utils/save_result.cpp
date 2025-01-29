#include "../include/utils.hpp"


void save_result(const int* matrix, int size) {
    std::ofstream file("result.txt");
    for (int y = 0; y < size; y++) {
        const cl_int* line = matrix + size * y;
        for (int x = 0; x < size - 1; x++) {
            file << *((int *)(line + x)) << " ";
        }
        file << *((int*)(line + size - 1)) << std::endl;
    }
}