#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <iostream>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
// Тип вложенного вектора
typedef boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager> ShmemAllocator;
typedef boost::interprocess::vector<int, ShmemAllocator> MyVector;
typedef boost::interprocess::allocator<MyVector, boost::interprocess::managed_shared_memory::segment_manager> VectorAllocator;
typedef boost::interprocess::vector<MyVector, VectorAllocator> MyVectorVector;

void vectorToMatrix(std::vector<std::vector<int>> &vector,
                    MyVectorVector &matrix,
                    boost::interprocess::managed_shared_memory &segment,
                    ShmemAllocator &alloc_inst)
{
    for (auto &vec : vector)
    {
        MyVector *myvector = segment.construct<MyVector>(boost::interprocess::anonymous_instance)(alloc_inst);
        for (auto &elem : vec)
        {
            myvector->push_back(elem);
        }
        matrix.push_back(*myvector);
    }
}

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

void printMatrix(MyVectorVector &matrix)
{
    for (const auto &vec : matrix)
    {
        for (auto elem : vec)
        {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "End of matrix;\n";
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

void multiplyMatrix(MyVectorVector &matrix1, MyVectorVector &matrix2)
{
  std::vector<std::vector<int>> result;

  for (auto rowIndex = 0; rowIndex < matrix1.size(); ++rowIndex)
  {
    result.emplace_back();
    result.back().reserve(matrix1[rowIndex].size());
    for (auto colIndex = 0; colIndex < matrix2.size(); ++colIndex)
    {
      result[rowIndex][colIndex] = 0;
      for (auto i = 0; i < matrix1.size(); ++i)
      {
        result[rowIndex][colIndex] += (matrix1[rowIndex][i] * matrix2[i][colIndex]);
      }
    }
  }

  for (auto rowIndex = 0; rowIndex < matrix1.size(); ++rowIndex)
  {
    for (auto colIndex = 0; colIndex < matrix2.size(); ++colIndex)
    {
      matrix1[rowIndex][colIndex] = result[rowIndex][colIndex];
    }
  }
  
}

int main()
{
    using namespace boost::interprocess;

    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Создание или открытие разделяемой памяти
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_or_create, "MySharedMemory", 65536);
    ShmemAllocator alloc_inst(segment.get_segment_manager());
    // Выделение памяти для вектора векторов

    VectorAllocator vector_alloc_inst(segment.get_segment_manager());
    segment.construct<MyVectorVector>("Matrix1")(vector_alloc_inst);
    segment.construct<MyVectorVector>("Matrix2")(vector_alloc_inst);
    segment.construct<bool>("Ready flag")(false);

    switch (auto pid = fork())
    {
        // весь код после fork() дважды:
        // в родительском процессе и в процессе потомке

    case -1:      // неудачная попытка создать процесс-потомок
        exit(-1); // выход из родительского процесса

    case 0:
    { // потомок

        // // Open the managed segment
        managed_shared_memory segment(open_only, "MySharedMemory");

        // Find the vector using the c-string name
        bool *flag = segment.find<bool>("Ready flag").first;
        auto *matrix1 = segment.find<MyVectorVector>("Matrix1").first;
        auto *matrix2 = segment.find<MyVectorVector>("Matrix2").first;
        while (!*flag)
        {
        }
        printMatrix(*matrix1);
        printMatrix(*matrix2);
        multiplyMatrix(*matrix1, *matrix2);

        switch (auto pid1 = fork())
        {
        case -1:
            exit(-1);
            break;
        case 0:
        {
            managed_shared_memory segment(open_only, "MySharedMemory");
            auto *matrix1 = segment.find<MyVectorVector>("Matrix1").first;
            printMatrix(*matrix1);
            break;
        }
        default:
            wait(&pid1);
            break;
        }
        exit(0);
    }
    default:
    { // родитель pid>0
        auto tmpMatrix1 = getMatrixFromFile("matrix");
        auto tmpMatrix2 = getMatrixFromFile("matrix2");
        printMatrix(tmpMatrix1);
        printMatrix(tmpMatrix2);
        managed_shared_memory segment(open_only, "MySharedMemory");
        ShmemAllocator alloc_inst(segment.get_segment_manager());
        auto *matrix1 = segment.find<MyVectorVector>("Matrix1").first;
        auto *matrix2 = segment.find<MyVectorVector>("Matrix2").first;
        vectorToMatrix(tmpMatrix1, *matrix1, segment, alloc_inst);
        vectorToMatrix(tmpMatrix2, *matrix2, segment, alloc_inst);
        printMatrix(*matrix1);
        printMatrix(*matrix2);
        bool *flag = segment.find<bool>("Ready flag").first;
        *flag = true;
        wait(&pid);
    }
    }

    return 0;
}