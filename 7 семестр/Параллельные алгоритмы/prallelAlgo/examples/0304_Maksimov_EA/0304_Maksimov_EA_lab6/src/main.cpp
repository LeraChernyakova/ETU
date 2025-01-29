#include <chrono>

#include "io/input.h"
#include "matrix/matrix.h"
#include "utils/utils.h"
#include "io/output.h"

int main() {
    // ==== Чтение параметров ====

    std::vector<int> inputValues = readInputFile();
    if(inputValues.size() != 1) {
        std::cout << "Incorrect input data!";
        return -1;
    }
    int N = inputValues[0];

    // ==== Получение матриц ====

    int* matrices[2];
    for(int i = 0; i < 2; i++) {
        matrices[i] = generateMatrixPlainArray(N);
    }
    cl_int* result = new cl_int[N*N];

    // ==== Подготовка ====

    // OpenCL
    cl_device_id device = createDevice();                                   // Устройство
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);   // Контекст
    cl_program program = buildProgram(ctx, device);                         // Для сборки программы из .cl-файла
    cl_kernel kernel = clCreateKernel(program, "multiplication", NULL);     // Kernel из программы, название в .cl
    cl_command_queue queue = clCreateCommandQueue(ctx, device, 0, NULL);    // Очередь команд

    // Данные
    cl_mem A = clCreateBuffer(
            ctx,
            CL_MEM_USE_HOST_PTR,
            sizeof(cl_int) * N*N,
            matrices[0],
            NULL
    );
    cl_mem B = clCreateBuffer(
            ctx,
            CL_MEM_USE_HOST_PTR,
            sizeof(cl_int) * N*N,
            matrices[1],
            NULL
    );
    cl_mem buffer = clCreateBuffer(
            ctx,
            CL_MEM_READ_WRITE,
            sizeof(cl_int) * N*N,
            NULL,
            NULL
    );

    // ==== Запуск ====

    auto timestampStart = std::chrono::high_resolution_clock::now();
    invokeKernel(
        kernel, queue,
        A, B, buffer, result,
        N
    );
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << "GPU multiplication, matrix size: " << N << ", time passed: " << timeDuration.count() << " ms." << std::endl;

    // ==== Запись ====

    if(openOutputFile()) {
        writeMatrixPlainArrayToFile(result, N);
        closeOutputFile();
    }

    // ==== Очистить данные после выполнения ====

    for(int i = 0; i < 2; i++) {
        delete[] matrices[i];
    }
    delete[] result;
    clReleaseKernel(kernel);
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);

    // ==== ====

    return 0;
}
