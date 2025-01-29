#include "opencl_handler.hpp"

using namespace std;


OpenCLWorker::OpenCLWorker(bool discreate_gpu) {
    // Отоносится к устройству конкретного устройства.
    if (discreate_gpu)
        device = create_device(1);
    else
        device = create_device(0);
    context = create_context(device);
    program = build_program(context, device);
    kernel = create_kernel(program);
    queue = create_queue(context, device);
}

OpenCLWorker::~OpenCLWorker() {
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);
}

cl_device_id OpenCLWorker::create_device(int platform_ind) {
    vector<cl_platform_id> platforms(2);
    cl_device_id device;
    int err;

    /* Получаем доступные платформы. */
    err = clGetPlatformIDs(2, platforms.data(), nullptr);
    if (err < 0) {
        cout << "Couldn't identify a platform." << endl;
        exit(1);
    } 

    /* Получаем доступное устройство. */
    err = clGetDeviceIDs(platforms[platform_ind], CL_DEVICE_TYPE_GPU, 1, &device, nullptr); // GPU
    if (err == CL_DEVICE_NOT_FOUND) {
        err = clGetDeviceIDs(platforms[platform_ind], CL_DEVICE_TYPE_CPU, 1, &device, nullptr); // CPU
    }
    if (err < 0) {
        cout << "Couldn't access any devices." << endl;
        exit(1);   
    }
    return device;
}

cl_context OpenCLWorker::create_context(cl_device_id device) {
    int err;

    /* Создаем контекст. */
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
    if (err < 0) {
        cout << "Couldn't create a context." << endl;
        exit(1);   
    }
   return context;
}

cl_program OpenCLWorker::build_program(cl_context context, cl_device_id device) {
    string kernel_code_string = read_file(PROGRAM_FILE);
    const char* kernel_code = kernel_code_string.data();
    size_t kernel_code_size = kernel_code_string.size();
    std::size_t found = kernel_code_string.find("__kernel");
    if (found == std::string::npos) {
        cout << "Couldn't read file of kernel program." << endl;
        exit(1); 
    }

    int err;

    /* Создаем объект программы. */
    cl_program program = clCreateProgramWithSource(context, 1, &kernel_code, &kernel_code_size, &err);
    if (err < 0) {
        cout << "Couldn't create the program." << endl;
        exit(1);
    }

    /* Компилируем программу для ядра. */
    err = clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
    if (err < 0) {
        /* Определяем, что пошло не так. */
        vector<char> program_log;
        size_t log_size;

        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &log_size);
        program_log.reserve(log_size + 1);
        program_log[log_size] = '\0';
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size + 1, program_log.data(), nullptr);
        cout << program_log.data() << endl;
        exit(1);
    }

    return program;
}

cl_command_queue OpenCLWorker::create_queue(cl_context context, cl_device_id device) {
    int err;

    /* Создаем очередь команд. */
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, nullptr, &err);
    if (err < 0) {
        cout << "Couldn't create a command queue." << endl;
        exit(1);   
    };

    return queue;
}

cl_kernel OpenCLWorker::create_kernel(cl_program program) {
    int err;

    /* Создаем ядро выполнения заданной программы. */
    cl_kernel kernel = clCreateKernel(program, KERNEL_FUNC, &err);
    if (err < 0) {
        cout << "Couldn't create a kernel" << endl;
        exit(1);
    };

    return kernel;
}

cl_mem OpenCLWorker::create_buffer(cl_mem_flags flags, size_t size, void* host_ptr) {
    int err;

    /* Cоздаем буфер для передачи данных между хостом и ядром. */
    cl_mem buffer = clCreateBuffer(context, flags, size, host_ptr, &err); 

    if (err < 0) {
        cout << "Couldn't create a buffer." << endl;
        exit(1);   
    };

    return buffer;
}

void OpenCLWorker::fill_buffer(cl_mem buffer, cl_bool blocking_read, size_t size, void* res_ptr) {
    int err;

    /* Заполняем буфер для ядра значениями. */
    err = clEnqueueWriteBuffer(queue, buffer, blocking_read, 0, size, res_ptr, 0, nullptr, nullptr);
    if (err < 0) {
        cout << "Couldn't fill buffer with values." << endl;
        exit(1);   
    };
}

void OpenCLWorker::read_buffer(cl_mem buffer, cl_bool blocking_read, 
                        size_t size, void* res_ptr) {
    int err;

    /* Считываем данные из буфера. */
    err = clEnqueueReadBuffer(queue, buffer, blocking_read, 0, size, res_ptr, 0, nullptr, nullptr);
    if(err < 0) {
        cout << "Couldn't read the data from buffer." << endl;
        exit(1);
    }
}

void OpenCLWorker::release_buffer(cl_mem buffer) {
    clReleaseMemObject(buffer);
} 

void OpenCLWorker::set_kernel_arg(uint arg_ind, size_t arg_size, const void* argument) {
    int err;

    /* Устанавливаем параметр необходимый программе, загруженной в ядро. */
    err = clSetKernelArg(kernel, arg_ind, arg_size, argument);
    if (err < 0) {
        cout << "Couldn't create a kernel argument: " << arg_ind << endl;
        exit(1);
    }
}

void OpenCLWorker::send_to_execution(cl_uint work_dim, const size_t* global_work_size, const size_t* local_work_size) {
    int err;

    /* Отправляем команду на исполнение кода ядра. */
    err = clEnqueueNDRangeKernel(queue, kernel, work_dim, nullptr, global_work_size, local_work_size, 0, nullptr, nullptr); 
    if (err < 0) {
        cout << "Couldn't enqueue the kernel." << endl;
        exit(1);
    }
}

void OpenCLWorker::wait_completion() {
    clFinish(queue);
}