#define CL_TARGET_OPENCL_VERSION 300
#define WG_SIZE 256

#include <math.h>
#include <chrono>
#include <CL/cl.h>

#include "./utility/opencl_handler.hpp"

using namespace std;
using namespace std::chrono;


void compute_fractal_on_device(
    int iterations, int width, int height, 
    float x_max, float y_max, int context_ind
) {
    system_clock::time_point start, end;
    double time_duration;

    // Создаем линейные векторы координат.
    std::vector<float> reals;
    std::vector<float> imags;

    for(int iy=0; iy < height; iy++) {
        for(int ix=0; ix < width; ix++) {
            reals.push_back(x_max * (((float)ix - width/2) / width));
            imags.push_back(y_max * (((float)iy - height/2) / height));
        }
    }

    std::vector<int> answers(reals.size());

    // Количество work items в каждой work group.
    size_t local_size = WG_SIZE;
    // Общее количество work items.
    size_t global_size = ceil(reals.size()/(float)local_size)*local_size;

    start = system_clock::now();
    // Инициализация OpenCL.
    cl_device_id device = create_device(0);
    cl_context context = create_context(device);
    cl_program program = build_program(context, device);
    cl_kernel kernel = create_kernel(program);
    cl_command_queue command_queue = create_queue(context, device);
    cl_mem buffer_reals = create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * reals.size(), nullptr);
    cl_mem buffer_imags = create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * imags.size(), nullptr);
    cl_mem buffer_answer = create_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * reals.size(), nullptr);

    // Заполняем буферы значениями.
    fill_buffer(command_queue, buffer_reals, CL_TRUE, sizeof(float) * reals.size(), reals.data());
    fill_buffer(command_queue, buffer_imags, CL_TRUE, sizeof(float) * imags.size(), imags.data());

    // Работа с ядром.
    set_kernel_arg(kernel, 0, sizeof(cl_mem), &buffer_reals);
    set_kernel_arg(kernel, 1, sizeof(cl_mem), &buffer_imags);
    set_kernel_arg(kernel, 2, sizeof(int), &iterations);
    set_kernel_arg(kernel, 3, sizeof(cl_mem), &buffer_answer);
    send_to_execution(command_queue, kernel, 1, &global_size, &local_size);

    // Ждем пока завершатся вычисления.
    clFinish(command_queue);

    // Читаем результаты.
    read_result_from_buf(
        command_queue, buffer_answer, CL_TRUE,
        sizeof(int) * reals.size(), answers.data()
    );
    end = system_clock::now();
    time_duration = duration<double>(end - start).count();

    cout << "GPU " << context_ind << "; x_max = " << x_max << "; y_max = " << y_max
         << "; width = " << width << "; height = " << height 
         << "; iterations = " << iterations << "; time took: " << time_duration << " s" << endl;

    // Отрисовываем полученный фрактал.
    ppm_draw("output/mandelbrot.ppm", answers, width, height, iterations);

    /* Освобождаем ресурсы. */
    clReleaseKernel(kernel);
    clReleaseMemObject(buffer_reals);
    clReleaseMemObject(buffer_imags);
    clReleaseMemObject(buffer_answer);
    clReleaseCommandQueue(command_queue);
    clReleaseProgram(program);
    clReleaseContext(context);
}


int main() {
    // Настройки фрактала Мальденброта.
    int iterations = 1000;
    int min_width = 2000;
    int min_height = 2000;
    float x_max = 1.0f;
    float y_max = 1.0f; 

    for (int context_ind=0; context_ind < 2; context_ind++) {
        for (int i = 1; i < 10; i++) {
            compute_fractal_on_device(
                iterations, min_width, min_height,
                x_max * i, y_max * i, context_ind
            );
        }
    }
    return 0;
}