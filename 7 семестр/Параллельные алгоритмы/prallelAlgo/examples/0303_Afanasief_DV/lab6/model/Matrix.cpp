#include "Matrix.h"

Matrix Matrix::generate(int size){
    Matrix result;
    result.size =std::make_pair(size, size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.m.emplace_back(rand()%40);
        }
    }
    return result;
}
