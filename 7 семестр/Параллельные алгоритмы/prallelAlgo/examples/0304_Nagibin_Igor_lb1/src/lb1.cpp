#include <iostream>
#include <thread>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>

const constexpr std::size_t MATRIX_SIZE = 720;

std::vector<std::vector<int>> GLOB_matrix1;
std::vector<std::vector<int>> GLOB_matrix2;
using Matrix = std::vector<std::vector<int>>;

void printMatrix(std::vector<std::vector<int>> &matrix)
{
  for (const auto &vec : matrix)
  {
    for (auto elem : vec)
    {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "End of vmatrix;\n";
}

std::vector<std::vector<int>> getMatrixFromFile(std::string filename)
{
  std::ifstream fin;
  std::cout << "~/Code/c++Tasks/lb1/" + filename << '\n';
  fin.open("./" + filename);
  if (!fin.is_open())
  {
    std::cout << "Ошибка открытия файла!" << std::endl;
  }
  std::vector<std::vector<int>> matr;
  std::string line;
  while (std::getline(fin, line))
  {
    std::istringstream iss(line);
    std::vector<int> vec;
    int num;
    while (iss >> num)
    {
      vec.push_back(num);
    }
    matr.push_back(vec);
  }
  fin.close();
  return matr;
}

void multiplyVectorMatrixRow(std::size_t rowIndex, Matrix &result)
{

  for (auto colIndex = 0; colIndex < MATRIX_SIZE; ++colIndex)
  {
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
      result[rowIndex][colIndex] += (GLOB_matrix1[rowIndex][i] * GLOB_matrix2[i][colIndex]);
    }
  }
}
void multiplyVectorMatrix()
{
  std::vector<std::vector<int>> &matrix1 = GLOB_matrix1;
  std::vector<std::vector<int>> &matrix2 = GLOB_matrix2;
  std::vector<std::vector<int>> result(matrix1.begin(), matrix1.end());

  for (auto rowIndex = 0; rowIndex < matrix1.size(); ++rowIndex)
  {
    for (auto colIndex = 0; colIndex < matrix2.size(); ++colIndex)
    {
      result[rowIndex][colIndex] = 0;
      for (int i = 0; i < matrix1.size(); ++i)
      {
        result[rowIndex][colIndex] += (matrix1[rowIndex][i] * matrix2[i][colIndex]);
      }
    }
  }
  std::copy(result.begin(), result.end(), matrix1.begin());
}
void readMatrixes()
{
  GLOB_matrix1 = getMatrixFromFile("matrix");
  GLOB_matrix2 = getMatrixFromFile("matrix2");
}
void threadsTest()
{
  std::thread matrixReading(readMatrixes);
  matrixReading.join();
  std::thread matrixMult(multiplyVectorMatrix);
  matrixMult.join();
  printMatrix(GLOB_matrix1);
}
void paralletMatrixMultiply(std::size_t thNumber)
{
  // инициализация матриц для умножения
  for (auto i = 0, val = 0; i < MATRIX_SIZE; ++i)
  {
    GLOB_matrix1.emplace_back();
    for (auto j = 0; j < MATRIX_SIZE; ++j, ++val)
    {
      GLOB_matrix1.back().push_back(val);
    }
  }
  for (const auto &vec : GLOB_matrix1)
  {
    GLOB_matrix2.emplace_back();
    for (auto elem : vec)
    {
      GLOB_matrix2.back().push_back(elem);
    }
  }
  
  std::vector<std::vector<int>> result; // инициализация матрицы результата
  for (const auto &vec : GLOB_matrix1)
  {
    result.emplace_back();
    for (auto elem : vec)
    {
      result.back().push_back(0);
    }
  }

  //Умножение 
  std::size_t rowIndex = 0;
  std::vector<std::thread> threads;
  for (auto i = 0; i < MATRIX_SIZE / thNumber; ++i)
  {

    for (auto j = 0; j < thNumber; ++j, ++rowIndex)
    {
      threads.push_back(std::move(std::thread(multiplyVectorMatrixRow, rowIndex, std::ref(result))));
    }
    for(auto& th: threads){
      th.join();
    }
    threads.clear();
  }
  // printMatrix(result);
}
int main()
{
  std::unordered_map<std::size_t, std::chrono::duration<double>> map;
  std::cout << "Есть " << std::thread::hardware_concurrency() << " потоков" << std::endl;
  std::cout << "Исследуем зависимость количества потоков от времени перемножения квадратной матрицы " << MATRIX_SIZE << "x" << MATRIX_SIZE <<std::endl;
  for(size_t i = 2; i < std::thread::hardware_concurrency(); ++i){
    if(MATRIX_SIZE % i == 0){
      auto start = std::chrono::high_resolution_clock::now();
      paralletMatrixMultiply(i);
      auto end = std::chrono::high_resolution_clock::now();
      map.insert({i, std::chrono::duration_cast<std::chrono::duration<double>>(end - start)});
      }
  }
  for(const auto& p: map){
    std::cout << "КОЛ-ВО ПОТОКОВ: " << p.first << " ||| ИТОГОВОЕ ВРЕМЯ: " << p.second.count()  << " c."<< std::endl;
  }
  return 0;
}