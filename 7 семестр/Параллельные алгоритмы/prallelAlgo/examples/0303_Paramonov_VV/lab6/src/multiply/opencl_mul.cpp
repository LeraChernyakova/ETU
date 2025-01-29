#include "multiply.hpp"
#include "../utility/opencl_handler.hpp"

using namespace std;


void opencl_mul(Matrix first, Matrix second, Matrix& result, size_t* local_size, size_t* global_size) {
    int* first_data = first.to_pointer();
    int* second_data = second.to_pointer();
    int* result_data = result.to_pointer();

    // Так как работаем с квадратными матрицами, то размер для всех одинаковый.
    int side = first.getRows(); 
    size_t mat_size = side * side * sizeof(int);

    // Инициализация OpenCL.
    OpenCLWorker worker(1);
    cl_mem buf_first_mat = worker.create_buffer(CL_MEM_READ_ONLY, mat_size, nullptr);
    cl_mem buf_second_mat = worker.create_buffer(CL_MEM_READ_ONLY, mat_size, nullptr);
    cl_mem buf_result_mat = worker.create_buffer(CL_MEM_WRITE_ONLY, mat_size, nullptr);

    // Заполняем буферы значениями.
    worker.fill_buffer(buf_first_mat, CL_TRUE, mat_size, first_data);
    worker.fill_buffer(buf_second_mat, CL_TRUE, mat_size, second_data);

    // Работа с ядром.
    worker.set_kernel_arg(0, sizeof(cl_mem), &buf_first_mat);
    worker.set_kernel_arg(1, sizeof(cl_mem), &buf_second_mat);
    worker.set_kernel_arg(2, sizeof(cl_mem), &buf_result_mat);
    worker.set_kernel_arg(3, sizeof(int),    &side);

    worker.send_to_execution(2, global_size, local_size);

    // Ждем пока завершатся вычисления.
    worker.wait_completion();

    // Читаем результаты.
    worker.read_buffer(buf_result_mat, CL_TRUE, mat_size, result_data);

    // Освобождаем буферы.
    worker.release_buffer(buf_first_mat);
    worker.release_buffer(buf_second_mat);
    worker.release_buffer(buf_result_mat);
}