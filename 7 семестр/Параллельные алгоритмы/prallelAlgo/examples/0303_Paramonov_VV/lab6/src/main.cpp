#include <math.h>
#include <chrono>
#include "multiply/multiply.hpp"

using namespace std;
using namespace std::chrono;
using namespace tbb;


int main() {
    int mat_sizes[] = { 128, 256, 512, 1024, 2048, 4096, 8192 };
    for (int mat_size : mat_sizes) {
        // Инициализация матриц.
        Matrix first(mat_size, mat_size, -5, 5);
        Matrix second(mat_size, mat_size, -5, 5);

        Matrix result_strassen(mat_size, mat_size);
        Matrix result_opencl(mat_size, mat_size);
        
        // Переменные для сохранения времени выполнения умножений.
        system_clock::time_point start_opencl, end_opencl;
        system_clock::time_point start_strassen, end_strassen;
        double duration_opencl, duration_strassen;

        // --------------------- Запускаем OpenCL умножение. ---------------------
        // Количество work items в каждой work group.
        size_t local_size[2] = { WG_SIZE, WG_SIZE };
        // Общее количество work items.
        size_t global_size[2] = { 
            (size_t)ceil(mat_size/(float)local_size[0])*local_size[0],
            (size_t)ceil(mat_size/(float)local_size[1])*local_size[1],  
        };

        start_opencl = system_clock::now();
        opencl_mul(first, second, result_opencl, local_size, global_size);
        end_opencl = system_clock::now();
        duration_opencl = duration<double>(end_opencl - start_opencl).count();

        // --------------------- Запускаем умножение Штрассена. ---------------------
        // Проверяем, что размеры матриц допустимы для применения данного метода умножения.
        int allow_recursion_depth = 6;
        if (first.getCols() != second.getCols() || first.getRows() != second.getRows() || first.getCols() != first.getRows()) {
            cout << "Матрицы должны быть квадратными." << endl;
            exit(1);
        }
        if ((first.getCols() % (1 << allow_recursion_depth)) != 0) {
            cout << "Матрицы должны иметь размер сторон, который делится на 2^" <<  allow_recursion_depth << "." << endl;
            exit(1);
        }

        start_strassen = system_clock::now();
        strassen_mul(first, second, result_strassen, 0, allow_recursion_depth); 
        end_strassen = system_clock::now();
        duration_strassen = duration<double>(end_strassen - start_strassen).count();

        // --------------------- Проверяем правильность результата. ---------------------
        if (!(result_strassen == result_opencl)) {
            cout << "Произошла ошибка расчета; результаты для двух методов не совпадают." << endl;
            exit(1);
        }

        cout << "Вычисление умножения матриц размером " << mat_size << " заняло времени: OpenCL: " << duration_opencl << " Штрассен: " <<  duration_strassen << endl;
    }
    
    return 0;
}