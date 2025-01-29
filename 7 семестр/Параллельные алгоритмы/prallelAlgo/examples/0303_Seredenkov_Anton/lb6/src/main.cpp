#include "matrix.h"

#define MATRIX_SIZE 4096
#define LOCAL_SIZE 32

#define CURRENT_TIME chrono::steady_clock::now()

cl_device_id create_device() {
	cl_platform_id platform;
	cl_device_id dev;
	clGetPlatformIDs(1, &platform, NULL);
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	return dev;
}

cl_program build_program(cl_context ctx, cl_device_id dev) {
	std::ifstream t("matrix.cl");
	std::string src((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();
	const char* src_text = src.data();
	size_t src_length = src.size();

	cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, NULL);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

	return program;
}


void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem& A, cl_mem& B, cl_mem& buff, cl_int* result, const size_t size) {
	clSetKernelArg(kernel, 0, sizeof(A), &A);
	clSetKernelArg(kernel, 1, sizeof(B), &B);
	clSetKernelArg(kernel, 2, sizeof(buff), &buff);
	clSetKernelArg(kernel, 3, sizeof(int), &size);


	size_t local_size[2] = { LOCAL_SIZE, LOCAL_SIZE };
	size_t global_size[2] = { size, size };
	clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(cl_int) * size * size, result, 0, NULL, NULL);

	clFinish(queue);
}

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
	return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}

int main() {
	cl_device_id device = create_device();
	cl_context context = clCreateContext(0, 1, &device, NULL, NULL, NULL);
	cl_program program = build_program(context, device);
	cl_kernel kernel = clCreateKernel(program, "matrix_mult", NULL);
	cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, NULL);

	Matrix first(MATRIX_SIZE, MATRIX_SIZE, true);
	Matrix second(MATRIX_SIZE, MATRIX_SIZE, true);

	cl_mem A = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, first.matrix.data(), NULL);
	cl_mem B = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, second.matrix.data(), NULL);
	cl_mem buff = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, NULL, NULL);

	std::vector<cl_int> result(MATRIX_SIZE * MATRIX_SIZE, 0);
	auto start = chrono::steady_clock::now();
	invoke_kernel(kernel, queue, A, B, buff, result.data(), MATRIX_SIZE);
	auto end = chrono::steady_clock::now();
	cout << "GPU time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

	//cout << "GPU_calc == A*B: " << (first*second == result);

	clReleaseKernel(kernel);
	clReleaseMemObject(A);
	clReleaseMemObject(B);
	clReleaseMemObject(buff);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);

	return 0;
}