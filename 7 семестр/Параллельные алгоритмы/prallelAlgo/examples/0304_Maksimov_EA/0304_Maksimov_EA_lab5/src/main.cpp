#include <chrono>

#include "io/input.h"
#include "mandelbrot/mandelbrot.h"
#include "utils/utils.h"
#include "io/output.h"

void runGPU(int resolution, int iterationsAmount) {
    
    // ==== Подготовка ====

    std::vector<cl_uint> pixels(resolution*resolution);                  // Пиксели для отрисовки
    cl_device_id device = createDevice();                                   // Устройство
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);   // Контекст
    cl_program program = buildProgram(ctx, device);                         // Для сборки программы из .cl-файла
    cl_kernel kernel = clCreateKernel(program, "mandelbrot", NULL);         // Kernel из программы, название в .cl
    cl_command_queue queue = clCreateCommandQueue(ctx, device, 0, NULL);    // Очередь команд
    cl_mem buffer = clCreateBuffer(                                         // Буфер для хранения результата
        ctx,
        CL_MEM_WRITE_ONLY,
        sizeof(cl_uint) * resolution*resolution,
        NULL,
        NULL
    );

    // ==== Запуск ====

    auto timestampStart = std::chrono::high_resolution_clock::now();
    invokeKernel(
        kernel, queue, buffer, pixels.data(),
        resolution, resolution,
        iterationsAmount
    );
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << "Graphics processing unit, time passed: " << timeDuration.count() << " ms." << std::endl;

    // ==== Запись ====

    if(openOutputFile(OUTPUT_FILE_GPU)) {
        writeResult(pixels.data(), resolution, resolution);
        closeOutputFile();
    }

    // ==== Очистить данные после выполнения ====

    clReleaseKernel(kernel);
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);
    return;
}

void runCPU(int resolution, int iterationsAmount) {
    
    // ==== Подготовка ====

    std::vector<cl_uint> pixels(resolution*resolution);     // Пиксели для отрисовки

    // ==== Запуск ====

    auto timestampStart = std::chrono::high_resolution_clock::now();
    drawMandelbrot(iterationsAmount, resolution, resolution, pixels.data());
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << "Central processing unit, time passed: " << timeDuration.count() << " ms." << std::endl;

    // ==== Запись ====

    if(openOutputFile(OUTPUT_FILE_CPU)) {
        writeResult(pixels.data(), resolution, resolution);
        closeOutputFile();
    }
}

int main() {

    // ==== Чтение параметров ====

    std::vector<int> inputValues = readInputFile();
    if(inputValues.size() != 2) {
        std::cout << "Incorrect input data!";
        return -1;
    }
    int resolution = inputValues[0];
    int iterationsAmount = inputValues[1];
    std::cout << "Mandelbrot resolution: " << resolution << "," << " iterations amount: " << iterationsAmount << "." << std::endl;

    // ==== Запуск ====

    runCPU(resolution, iterationsAmount);
    runGPU(resolution, iterationsAmount);

    // ==== ====

    return 0;
}
