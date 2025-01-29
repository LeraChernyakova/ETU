#include "Matrix.h"
//first-height, second-width
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

Matrix::Matrix(int height, int width) {
    for(int i = 0; i < height; i++){
        std::vector<int> row(width);
        m.push_back(row);
    }
}

Matrix operator+(const Matrix& left,const Matrix& right){
    Matrix result(left.size().first, left.size().second);
    for (int i = 0; i < result.size().first; i++) {
        for (int j = 0; j < result.size().second; j++) {
            result.m[i][j] = left.m[i][j] + right.m[i][j];
        }
    }
    return result;
}
Matrix operator-(const Matrix& left,const Matrix& right){
    Matrix result(left.size().first, left.size().second);
    for (int i = 0; i < result.size().first; i++) {
        for (int j = 0; j < result.size().second; j++) {
            result.m[i][j] = left.m[i][j] - right.m[i][j];
        }
    }
    return result;
}
