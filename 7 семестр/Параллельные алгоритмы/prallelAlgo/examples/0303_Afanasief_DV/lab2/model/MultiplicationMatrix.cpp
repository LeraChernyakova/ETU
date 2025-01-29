#include "MultiplicationMatrix.h"

MultiplicationMatrix MultiplicationMatrix::create(Matrix left, Matrix right){
    
    if(left.size().second != right.size().first){
        throw std::runtime_error("Wrong size matrix");
    }
    return MultiplicationMatrix(left, right);
    
}
int MultiplicationMatrix::multiplyColumnRow(int i, int j){
    int result = 0;
    for(int iter = 0; iter < this->left.size().second; iter++) {
        result += this->left.m[i][iter] * this->right.m[iter][j];
    }
    return result;
}

void MultiplicationMatrix::multiplyRowThread(int i, std::promise<std::vector<int>>& result){
    result.set_value(multiplyRow(i));
}

std::vector<int> MultiplicationMatrix::multiplyRow(int i){
    std::vector<int> result;
    for(int iter = 0; iter < this->right.size().second; iter++) {
        result.emplace_back(this->multiplyColumnRow(i, iter));
    }
    return result;
}
Matrix MultiplicationMatrix::multiply(){
    Matrix ans;
    for(int iter = 0; iter < this->left.size().first; iter++){
        ans.m.emplace_back(this->multiplyRow(iter));
    }
    return ans;
}