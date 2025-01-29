#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include<vector>
#include <chrono>
#include<CL/opencl.hpp>
#include "mandelbrot.h"

#define CURRENT_TIME chrono::steady_clock::now()
#define CL_FILENAME "mandelbrot.cl"

using namespace std;

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
	return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}



int align(int x, int y) {
	return (x + y - 1) / y * y;
}


void save_ppm(const cl_uint* p, int w, int h, const char* output_name) {
	std::ofstream file(output_name, std::ios::binary);
	file << "P6\n" << w << " " << h << "\n255\n";
	for (int y = 0; y < h; ++y) {
		const cl_uint* line = p + w * y;
		for (int x = 0; x < w; x++) {
			file.write((const char*)(line + x), 3);
		}
	}
}



cl_device_id create_device() {
	cl_platform_id platform;
	cl_device_id dev;
	cl_int err = 0;
	err |= clGetPlatformIDs(1, &platform, NULL);
	err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	if (err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
	}
	if (err) throw;
	return dev;
}

cl_program build_program(cl_context ctx, cl_device_id dev) {
	int err = 0;

	// получение текста кода для kernel
	std::ifstream t(CL_FILENAME);
	std::string src((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();
	const char* src_text = src.data();
	size_t src_length = src.size();
	
	// загрузка текста kernel в программу
	cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);
	//cout << "Error during program call " << err << '\n';
	// собираем программу
	err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	//cout << "Error during building program " << err << '\n';
	
	if (err) throw;

	return program;
}


void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem buff,
	cl_uint* result, float x, float y, float mag, int w, int h, int iters) {
	cl_int err = 0;
	// установка аргументов для kernel
	err |= clSetKernelArg(kernel, 0, sizeof(float), &x); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 1, sizeof(float), &y); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 2, sizeof(float), &mag); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 3, sizeof(int), &iters); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 4, sizeof(int), &w); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 5, sizeof(int), &h); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 6, sizeof(buff), &buff); // cout << "Error during setting kernel arg " << err << '\n';
	err |= clSetKernelArg(kernel, 7, sizeof(int), &w); // cout << "Error during setting kernel arg " << err << '\n';

	
	size_t local_size[2] = { 256, 1 }; // размер рабочей группы
	size_t global_size[2] = { align(w, local_size[0]), align(h, local_size[1]) }; // размер рабочего пространства/контекста NDRange
	//cout << "global size = " << global_size[0] << ' ' << global_size[1] << '\n';
	// запускаем двумерную задачу
	err |= clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
	//cout << "Error during enqueueNDRangeKernel " << err << '\n';
	// читаем результат
	err |= clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(int) * w * h, result, 0, NULL, NULL);
	// ждём завершения всех операций
	clFinish(queue);
}



int main() {
	
	// ширина и высота выходного изображения
	const int res_w = 4096, res_h = 2048;
	cl_int err = 0;
	// получаем девайс
	cl_device_id device = create_device();
	// создаем контекст
	cl_context context = clCreateContext(0, 1, &device, NULL, NULL, NULL);

	// вызвали функцию сборки
	cl_program program = build_program(context, device);

	// получаем Kernel
	cl_kernel kernel = clCreateKernel(program, "mandelbrot", &err);
	//cout << "Error during creating kernel " << err << '\n';

	// создаём очередь
	cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
	//cout << "Error during creating command queue " << err << '\n';

	// создаём буфер для результата
	cl_mem buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_uint) * res_w * res_h, NULL, NULL);

	std::vector<cl_uint> pixels(res_w * res_h);
	auto start = CURRENT_TIME;
	invoke_kernel(kernel, queue, buff, pixels.data(), -.5f, 0, 4.5f, res_w, res_h, 100);
	cout << "GPU: " << get_time_diff(start, CURRENT_TIME) << " ms\n";
	save_ppm(pixels.data(), res_w, res_h, "gpu_res.ppm");

	
	//cout << CL_INVALID_PROGRAM_EXECUTABLE << '\n';
	//cout << CL_INVALID_COMMAND_QUEUE << '\n';
	//cout << CL_INVALID_KERNEL << '\n';
	//cout << CL_INVALID_CONTEXT << '\n';
	//cout << CL_INVALID_KERNEL_ARGS << '\n';
	//cout << CL_INVALID_WORK_DIMENSION << '\n';
	//cout << CL_INVALID_WORK_GROUP_SIZE << '\n';
	//cout << CL_INVALID_WORK_GROUP_SIZE << '\n';
	//cout << CL_INVALID_WORK_GROUP_SIZE << '\n';
	
	// освобождение ресурсов
	clReleaseKernel(kernel);
	clReleaseMemObject(buff);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);
	


	std::vector<unsigned int> proc_pxls(res_w * res_h);
	start = CURRENT_TIME;
	mandelbrot(-0.5, 0, 4.5f, 100, res_w, res_h, proc_pxls.data(), res_w);
	cout << "CPU: " << get_time_diff(start, CURRENT_TIME) << " ms\n";

	save_ppm(proc_pxls.data(), res_w, res_h, "proc_res.ppm");
	
	
	return 0;
}





