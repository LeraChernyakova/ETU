#include "matrix.h"
Matrix::Matrix(){};

Matrix::Matrix(int N, int M)
{
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<> distrib(0, 9); 
    matrix = std::vector<std::vector<int>> (N);
    for (int i = 0; i < N; i++) 
    {
        matrix[i].reserve(M);
        for (int j = 0;j < M;j++) 
        {
            matrix[i].push_back(distrib(generator)); 
        }
    }
}
void Matrix::multiple(Matrix& second,Matrix& result)
{
    int rowResult = result.matrix.size(); // количество элементов в столбце финальной матрице
    int columnResult = result.matrix[0].size(); // количество элементов в строке финальной матрицы
    for(int row = 0;row < rowResult;row++){

        for(int col = 0; col < columnResult;col++){
            result.matrix[row][col] = 0;
            for(int i = 0; i < second.matrix.size();i++){
                result.matrix[row][col] += matrix[row][i] * second.matrix[i][col];
            }
        }
    }
}



void Matrix::multipleExtend(Matrix& second,Matrix& result,int startRow,int endRow)
{
    int rowResult = result.matrix.size(); // количество элементов в столбце финальной матрице
    int columnResult = result.matrix[0].size(); // количество элементов в строке финальной матрицы
    std::vector<std::vector<long long int>> bt;
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < rowResult; j++) {

            result.matrix[i][j] = 0;
            for (int k = 0; k < columnResult; k++) {
                result.matrix[i][j] += matrix[i][k] * second.matrix[j][k];
            }
        }
    }
}

void Matrix::transp(Matrix& mat){
    for(int i = 0; i< mat.matrix.size();i++){
        for(int j = 0; j< mat.matrix[0].size();j++){
        matrix[i][j] = mat.matrix[j][i];
    }
    }
}

void Matrix::multiple(Matrix& second,Matrix& result,int shiftRow,int threadCount)
{
    int rowResult = result.matrix.size(); // количество элементов в столбце финальной матрице
    int columnResult = result.matrix[0].size(); // количество элементов в строке финальной матрицы
    for(int row = shiftRow;row < rowResult;row+= threadCount){

        for(int col = 0; col < columnResult;col++){
			
            result.matrix[row][col] = 0;
            for(int i = 0; i < second.matrix.size();i++){
                result.matrix[row][col] += matrix[row][i] * second.matrix[i][col];
            }
        }
    }
}

void Matrix::fileOutput(std::string fileName)
{
    std::ofstream fout(fileName);
    for(int row = 0; row < matrix.size(); row++) 
    {
        for(int column = 0; column < matrix[row].size(); column++) 
        {
            fout << matrix[row][column] << " ";
        }
        fout << std::endl;
    }
    fout.close();
}

Matrix operator+(Matrix first, Matrix second){
    int count_rows = first.matrix.size();
    int count_columns = first.matrix[0].size();
    Matrix result(count_rows, count_columns);
    for(auto row = 0; row < result.matrix.size(); row++) {
    for(auto column = 0; column < result.matrix[row].size(); column++) {
            result.matrix[row][column] =first.matrix[row][column] + second.matrix[row][column];
        }
    }
    return result;
}
Matrix Matrix::operator=(Matrix copy)
{
    matrix =   copy.matrix;
    return *this;

}

Matrix operator-(Matrix first, Matrix second){
    int count_rows    = first.matrix.size();
    int count_columns = first.matrix[0].size();
    Matrix result(count_rows, count_columns);
    for(auto row = 0; row < result.matrix.size(); row++) {
    for(auto column = 0; column < result.matrix[row].size(); column++) {
            result.matrix[row][column] =first.matrix[row][column] - second.matrix[row][column];
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix)
{
    out << matrix.matrix.size() << ' ';
    out << matrix.matrix[0].size() << '\n';

    for (int i = 0; i < matrix.matrix.size(); ++i)
    {
        for (int j = 0; j < matrix.matrix[0].size(); ++j)
        {
            out << matrix.matrix[i][j];
            if (j < matrix.matrix[0].size() - 1)
            {
                out << ' ';
            }
        }
        out << '\n';
    }

    return out;
}
