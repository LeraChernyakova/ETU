#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <CL/cl.h>
#include <libclew/ocl_init.h>
#include <matrix.h>
const int MATRIX_SIZE = 2048;
const int LOCAL_SIZE = 16;


std::string check_res(Matrix a, vector<cl_int> b) {
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.matrix[i * a.cols + j] != b[i * a.cols + j]) {
				return "Matrices are NOT equal(";
			}
		}
	}
	return "Matrices ARE equal!!!";
}



cl_device_id create_device() {
    cl_platform_id platform;
    cl_device_id device;
    cl_uint platformsCount = 0;
    clGetPlatformIDs(0, nullptr, &platformsCount);
    std::vector<cl_platform_id> platforms(platformsCount);
    clGetPlatformIDs(platformsCount, platforms.data(), nullptr);
    clGetDeviceIDs(platforms[1], CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    return device;
}

cl_program build_program(cl_context ctx, cl_device_id dev) {
	int err = 0;

	std::ifstream t("./m_mult.cl");
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




void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem& A, cl_mem& B, cl_mem& buff,
	cl_int* result) {
	cl_int err = 0;
	err |= clSetKernelArg(kernel, 0, sizeof(A), &A);  
	//std::cout << "err1 = " << err << std::endl;
	err |= clSetKernelArg(kernel, 1, sizeof(B), &B);  
	//std::cout << "err2 = " << err << std::endl;
	err |= clSetKernelArg(kernel, 2, sizeof(buff), &buff);  
	//std::cout << "err3 = " << err << std::endl;
	err |= clSetKernelArg(kernel, 3, sizeof(int), &MATRIX_SIZE);
	//std::cout << "err4 = " << err << std::endl;
	
	
	size_t local_size[2] = { LOCAL_SIZE, LOCAL_SIZE }; 
	size_t global_size[2] = { MATRIX_SIZE, MATRIX_SIZE }; 

	err |= clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, result, 0, NULL, NULL);

	clFinish(queue);
}




int main() {
    if (!ocl_init()) throw;
    cl_device_id device = create_device();
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    cl_program program = build_program(context, device);
    cl_int buff_error = 0;
    cl_int err = 0;
	cl_kernel kernel = clCreateKernel(program, "matrix_mult", &err);
	//std::cout << "err5 = " << err << std::endl;
	cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
	
	Matrix left(MATRIX_SIZE, MATRIX_SIZE, true);
	Matrix right(MATRIX_SIZE, MATRIX_SIZE, true);
	
	cl_mem A = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, left.matrix.data(), &buff_error);
	//std::cout << "err7 = " << buff_error << std::endl;
	if (buff_error) cout << "Error while creating buffer A\n";
	cl_mem B = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, right.matrix.data(), &buff_error);
	//std::cout << "err8 = " << buff_error << std::endl;
	if (buff_error) cout << "Error while creating buffer B\n";
	cl_mem buff = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, NULL, &buff_error);
	if (buff_error) cout << "Error while creating result buffer\n";
	//std::cout << "err9 = " << buff_error << std::endl;
	std::vector<cl_int> result(MATRIX_SIZE * MATRIX_SIZE, 0);
	
	auto start_programm = std::chrono::high_resolution_clock::now();
	
	invoke_kernel(kernel, queue, A, B, buff, result.data());
	
	auto end_programm = std::chrono::high_resolution_clock::now();
    	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_programm - start_programm);
	std::cout << "GPU time: " << duration.count() << std::endl;
	//for (auto i = 0; i<result.size(); i++) {
	//	std::cout << result[i] << " ";
	//}
	auto check_help = left * right;
	cout << "RES: " << check_res(check_help, result) << std::endl;
	//std::cout << check_help << std::endl;

	clReleaseKernel(kernel);
	clReleaseMemObject(A);
	clReleaseMemObject(B);
	clReleaseMemObject(buff);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);
	
	return 0;
}
