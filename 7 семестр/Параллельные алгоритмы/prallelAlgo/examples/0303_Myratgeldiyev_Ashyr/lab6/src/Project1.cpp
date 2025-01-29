#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include<vector>
#include <chrono>
#include "matrix.h"

#define CURRENT_TIME chrono::steady_clock::now()
#define CL_FILENAME "m_mult.cl"
#define MATRIX_SIZE 4096
#define LOCAL_SIZE 32 // block size

using namespace std;


unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
	return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}

bool check_res(const Matrix& a, vector<cl_int>& const b) {
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.matrix[i * a.cols + j] != b[i * a.cols + j]) {
				return false;
			}
		}
	}
	return true;
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

	std::ifstream t(CL_FILENAME);
	std::string src((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();
	src = "#define BS " + to_string(LOCAL_SIZE) + "\n\n" + src;
	const char* src_text = src.data();
	size_t src_length = src.size();
	
	cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);
	err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	
	if (err) {
		cout << "Thrown error " << err << '\n';
			// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

			// Allocate memory for the log
		char* log = new char[log_size];

			// Get the log
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

			// Print the log
		printf("%s\n", log);
		delete[] log;
		throw;
	};

	return program;
}


unsigned long invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem& A, cl_mem& B, cl_mem& buff,
	cl_int* result, const int size) {
	cl_int err = 0;
	err |= clSetKernelArg(kernel, 0, sizeof(A), &A);  
	err |= clSetKernelArg(kernel, 1, sizeof(B), &B);  
	err |= clSetKernelArg(kernel, 2, sizeof(buff), &buff);  
	err |= clSetKernelArg(kernel, 3, sizeof(int), &size);
	
	
	size_t local_size[2] = { LOCAL_SIZE, LOCAL_SIZE }; 
	size_t global_size[2] = { size, size }; 

	auto start = CURRENT_TIME;
	err |= clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(cl_int) * size * size, result, 0, NULL, NULL);

	clFinish(queue);
	return get_time_diff(start, CURRENT_TIME);
}



int main() {
	if (MATRIX_SIZE % LOCAL_SIZE) {
		cout << "Global size (MATRIX_SIZE) is not multiple of LOCAL_SIZE\n";
		return -1;
	}

	cl_int err = 0;
	cl_device_id device = create_device();
	cl_context context = clCreateContext(0, 1, &device, NULL, NULL, NULL);
	cl_program program = build_program(context, device);
	cl_int buff_error = 0;
	cl_kernel kernel = clCreateKernel(program, "matrix_mult", &err);
	cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
	
	Matrix left(MATRIX_SIZE, MATRIX_SIZE, true);
	Matrix right(MATRIX_SIZE, MATRIX_SIZE, true);
	
	cl_mem A = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, left.matrix.data(), &buff_error);
	if (buff_error) cout << "Error while creating buffer A\n";
	cl_mem B = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, right.matrix.data(), &buff_error);
	if (buff_error) cout << "Error while creating buffer B\n";
	cl_mem buff = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, NULL, NULL);
	if (buff_error) cout << "Error while creating result buffer\n";
	std::vector<cl_int> result(MATRIX_SIZE * MATRIX_SIZE, 0);
	
	auto gpu_time = invoke_kernel(kernel, queue, A, B, buff, result.data(), MATRIX_SIZE);
	cout << "GPU: " << gpu_time << " ms\n";
	//cout << "RES: " << check_res(left * right, result);

	clReleaseKernel(kernel);
	clReleaseMemObject(A);
	clReleaseMemObject(B);
	clReleaseMemObject(buff);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);
	
	return 0;
}





