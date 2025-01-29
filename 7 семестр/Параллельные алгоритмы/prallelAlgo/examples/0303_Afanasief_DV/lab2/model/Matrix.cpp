#include "Matrix.h"
std::pair<unsigned int, unsigned int> Matrix::size() const{
    if(m.empty())
        return std::make_pair(0, 0);
    return std::make_pair(m.size(),m[0].size());
}

Matrix Matrix::generate(){
    Matrix result;
    for(int i = 0; i < 4; i++){
        std::vector<int> row;
        for(int j = 0; j < 4; j++){
            row.emplace_back(rand()%40);
        }
        result.m.push_back(row);
    }
    return result;
}
Matrix Matrix::generate(int size){
    Matrix result;
    for(int i = 0; i < size; i++){
        std::vector<int> row;
        for(int j = 0; j < size; j++){
            row.emplace_back(rand()%40);
        }
        result.m.push_back(row);
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Matrix& obj){
    std::pair<unsigned int, unsigned int> s = obj.size();
    out << s.first << ' ' << s.second << '\n';
    for(int i = 0; i < s.first; i++){
        for(int j = 0; j < s.second; j++){
            out << obj.m[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}
std::istream& operator>>(std::istream& is, Matrix& obj){
    unsigned int rows, columns;
    is >> rows >> columns;
    for(int i = 0; i < rows; i++){
        std::vector<int> row;
        for(int j = 0; j < columns; j++){
            int value;
            is >> value;
            row.emplace_back(value);
        }
        obj.m.push_back(row);
    }
    return is;
}

std::pair<Matrix, int*> Matrix::readFromPtr(int* ptr){
    int width = *ptr;
    std::cout << *ptr << '\n';
    ptr++;

    int height = *ptr;
    std::cout << *ptr << '\n';
    ptr++;
    Matrix result;
    for (int i = 0; i < width; i++) {
        std::vector<int> row;
        for (int j = 0; j < height; j++) {
            row.emplace_back(*ptr);
            std::cout << *ptr << ' ';
            ++ptr;
        }
        std::cout << '\n';
        result.m.emplace_back(row);
    }
    return std::make_pair(result, ptr);
}
int* Matrix::writeToPtr(int* ptr) const{
    auto s = this->size();
    *ptr = s.first;
    ++ptr;
    *ptr = s.second;
    ++ptr;
    for (int i = 0; i < s.first; ++i) {
        for (int j = 0; j < s.second; ++j) {
            *ptr = m[i][j];
            ++ptr;
        }
    }
    return ptr;
}