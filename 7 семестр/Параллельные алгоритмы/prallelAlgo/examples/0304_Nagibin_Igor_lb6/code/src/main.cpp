#include <CL/cl.h>
#include <libclew/ocl_init.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include "matrix_cl.h"
#include "matrixfunctions.hpp"

void test(size_t size){
    auto m1 = generateMatrix(size);
    auto m2 = generateMatrix(size);
    auto tmp = MatrixCl(m1, m2, 10);
    if(tmp.isError()){
        std::cout << "ERROR \n";
        return ;
    }
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    auto res = tmp.getResut();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Размер матрицы: " << size << " X " << size << "; Время: " 
    << std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count() << '\n';
}

int main(){
    for(size_t size = 1 << 6; size < 1 << 30; size = size << 1){
        test(size);
    }
    return 0;
}