#include "matrix.h"


Matrix::Matrix(){};

Matrix::Matrix(int N, int M)
{
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<> distrib(0, 9); 

    matrix = std::vector<std::vector<int>> (N);
//    std::cout << "|||||Начало создания|||||" <<std::endl;
    for (int i = 0; i < N; i++) {
        matrix[i].reserve(M);
        for (int j = 0;j < M;j++) {
             matrix[i].push_back(distrib(generator)); // генерируем случайное число из диапазона с равномерным распределением для каждой ячейки
    //    std::cout << matrix[i][j] << " ";
	}
//	std::cout << std::endl;
    }
  //  std::cout << "|||||Конец создания|||||" <<std::endl;


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

int * Matrix::toArray()
{
    int count = matrix.size() * matrix[0].size();
    int *buf = new int[count];
    int index = 0;
    for(int row = 0; row < matrix.size(); row++) {
        for(int column = 0; column < matrix[row].size(); column++) {
            buf[index] = matrix[row][column]; // записываем представление матрицы в массив int для записи и чтения дескриптора
            index++;
            }
        }
    return buf;
}

void Matrix::fromArray(int* buf,int N, int M)
{
    matrix = std::vector<std::vector<int>> (N);
    for (int i = 0; i < N; i++) {
        matrix[i].resize(M);
    }
    int index = 0;
    for(int row = 0; row < matrix.size(); row++) {
        for(int column = 0; column < matrix[row].size(); column++) {
            matrix[row][column] = buf[index]; // преобразуем массив int в матрицу
            index++;
        }
    }
}

void Matrix::fileOutput(char* fileName) // печать матрицы в файл
{
        std::ofstream fout(fileName);
        for(int row = 0; row < matrix.size(); row++) {
            for(int column = 0; column < matrix[row].size(); column++) {
                fout << matrix[row][column] << " ";
                }
            fout << std::endl;
            }
        fout.close();
}
