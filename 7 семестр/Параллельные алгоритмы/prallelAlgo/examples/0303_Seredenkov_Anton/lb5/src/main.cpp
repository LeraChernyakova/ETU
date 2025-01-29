#include <chrono>
#include "mandelbrot_cpu.h"
#include "mandelbrot_gpu.h"

#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

int main() {
	static const int res_w = 4096, res_h = 4096; // определяем размер изображения
	int max_iters = 50;
	cl_device_id device = get_device(); // создаём устройство
	cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL); // создаём контекст
	cl_program program = build_program(ctx, device); // вызываем функцию сборки программы
	cl_kernel kernel = clCreateKernel(program, "mandelbrot", NULL); // получаем kernel из программы
	cl_command_queue queue = clCreateCommandQueueWithProperties(ctx, device, 0, NULL); // создаём очередь
	cl_mem buffer = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, sizeof(cl_uint) * res_w * res_h, NULL,NULL); // создаём буффер для сохранения результата
	std::vector<cl_uint> pixGPU(res_w * res_h); // выделить буффер 

	auto startTime = std::chrono::steady_clock::now();
	invoke_kernel(kernel, queue, buffer, pixGPU.data(), res_w, res_h, max_iters);// отрисовка фрактала

	std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime;
	std::cout << "GPU Time: " << endTime.count() << " seconds" << std::endl;
	save_image(pixGPU.data(), res_w, res_h, "GPU.ppm"); // сохранить файл

	clReleaseKernel(kernel); // очистка данных
	clReleaseMemObject(buffer);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(ctx);

	std::vector<cl_uint> pixCpu(res_w * res_h); // выделить буффер 
	auto startTimeCpu = std::chrono::steady_clock::now(); // засечь время начала
	mandelbrot(max_iters, res_w, res_h, pixCpu.data());
	std::chrono::duration<double> endTimeCpu = std::chrono::steady_clock::now() - startTimeCpu; // закончить время подсчёта
	std::cout << "CPU Time: " << endTimeCpu.count() << " seconds" << std::endl;
	save_image(pixCpu.data(), res_w, res_h, "CPU.ppm");

	return 0;
}