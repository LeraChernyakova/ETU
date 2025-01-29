#include <CL/cl.h>
#include <libclew/ocl_init.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

template<typename T>
std::string to_string(T value) {
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

void reportError(cl_int err, const std::string &filename, int line) {
    if (CL_SUCCESS == err)
        return;

    // Таблица с кодами ошибок:
    // libs/clew/CL/cl.h:103
    std::string message = "OpenCL error code " + to_string(err) + " encountered at " + filename + ":" + to_string(line);
    throw std::runtime_error(message);
}

typedef unsigned char uchar;

#define OCL_SAFE_CALL(expr) reportError(expr, __FILE__, __LINE__)

#ifndef KERNEL_FILE_PATH
#define KERNEL_FILE_PATH "mandelbrot.cl"
#endif

void write_to_ppm(const uchar *image, int width, int height, const char *filename) {
    FILE *fp = fopen(filename, "wb"); // Open file for writing in binary mode
    if (!fp) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Write the PPM header: P6 format, width, height, and max color value
    fprintf(fp, "P6\n%d %d\n255\n", width, height);

    // Write the pixel data: for grayscale, repeat the value for R, G, and B
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uchar pixel = image[y * width + x];
            for (int color = 0; color < 3; ++color) { // Write R, G, B channels
                fwrite(&pixel, 1, 1, fp);
            }
        }
    }

    fclose(fp);
}

void write_to_ppm_ascii(const uchar *image, int width, int height, const char *filename) {
    FILE *fp = fopen(filename, "w"); // Open file for writing in text mode
    if (!fp) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Write the PPM header
    fprintf(fp, "P3\n%d %d\n255\n", width, height);

    // Write the pixel data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uchar pixel = image[y * width + x];
            fprintf(fp, "%d %d %d ", pixel, pixel, pixel); // R, G, B
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int main() {
    // Пытаемся слинковаться с символами OpenCL API в runtime (через библиотеку libs/clew)
    if (!ocl_init())
        throw std::runtime_error("Can't init OpenCL driver!");

    // Откройте
    // https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/
    // Нажмите слева: "OpenCL Runtime" -> "Query Platform Info" -> "clGetPlatformIDs"
    // Прочитайте документацию clGetPlatformIDs и убедитесь, что этот способ узнать, сколько есть платформ, соответствует документации:
    cl_uint platformsCount = 0;
    OCL_SAFE_CALL(clGetPlatformIDs(0, nullptr, &platformsCount));
    std::cout << "Number of OpenCL platforms: " << platformsCount << std::endl;

    // Тот же метод используется для того, чтобы получить идентификаторы всех платформ - сверьтесь с документацией, что это сделано верно:
    std::vector<cl_platform_id> platforms(platformsCount);
    OCL_SAFE_CALL(clGetPlatformIDs(platformsCount, platforms.data(), nullptr));

    cl_device_id selected_device = nullptr;

    for (int platformIndex = 0; platformIndex < platformsCount; ++platformIndex) {
        std::cout << "Platform " << (platformIndex + 1) << "/" << platformsCount << std::endl;
        cl_platform_id platform = platforms[platformIndex];

        // Откройте документацию по "OpenCL Runtime" -> "Query Platform Info" -> "clGetPlatformInfo"
        // Не забывайте проверять коды ошибок с помощью макроса OCL_SAFE_CALL
        size_t platformNameSize = 0;
        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, nullptr, &platformNameSize));// TODO 1.1
        // Попробуйте вместо CL_PLATFORM_NAME передать какое-нибудь случайное число - например 239
        // Т.к. это некорректный идентификатор параметра платформы - то метод вернет код ошибки
        // Макрос OCL_SAFE_CALL заметит это, и кинет ошибку с кодом
        // Откройте таблицу с кодами ошибок:
        // libs/clew/CL/cl.h:103
        // Найдите там нужный код ошибки и ее название
        // Затем откройте документацию по clGetPlatformInfo и в секции Errors найдите ошибку, с которой столкнулись
        // в документации подробно объясняется, какой ситуации соответствует данная ошибка, и это позволит, проверив код, понять, чем же вызвана данная ошибка (некорректным аргументом param_name)
        // Обратите внимание, что в этом же libs/clew/CL/cl.h файле указаны всевоможные defines, такие как CL_DEVICE_TYPE_GPU и т.п.

        // TODO 1.2
        // Аналогично тому, как был запрошен список идентификаторов всех платформ - так и с названием платформы, теперь, 
        //когда известна длина названия - его можно запросить:
        std::vector<unsigned char> platformName(platformNameSize, 0);
        
        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_NAME, platformNameSize, platformName.data(), &platformNameSize));
        std::cout << "    Platform name: " << platformName.data() << std::endl;

        // TODO 1.3
        // Запросите и напечатайте так же в консоль вендора данной платформы

        size_t platformVendorSize = 0;
        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, nullptr, &platformVendorSize));        
        
        std::vector<unsigned char> platformVendor(platformVendorSize, 0);

        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, platformVendorSize, platformVendor.data(), &platformVendorSize));
        std::cout << "    Platform vendor: " << platformVendor.data() << std::endl;


        // TODO 2.1
        // Запросите число доступных устройств данной платформы (аналогично тому, 
        //как это было сделано для запроса числа доступных платформ - см. секцию "OpenCL Runtime" -> "Query Devices")
        cl_uint devicesCount = 0;
        cl_uint num_entries = 0;
        OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &devicesCount));
        std::cout << "      Number of OpenCL dev-s: " << devicesCount << std::endl; 
        std::vector<cl_device_id> devices (devicesCount);
        OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, devices.data(), &devicesCount));
        
        for (int deviceIndex = 0; deviceIndex < devicesCount; ++deviceIndex) {
            // TODO 2.2
            // Запросите и напечатайте в консоль:
            // - Название устройства
            // - Тип устройства (видеокарта/процессор/что-то странное)
            // - Размер памяти устройства в мегабайтах
            // - Еще пару или более свойств устройства, которые вам покажутся наиболее интересными

            std::cout << "    >> DEVICE #" << (deviceIndex + 1) << "/" << devicesCount << std::endl;

            cl_device_id device = devices[deviceIndex];

            size_t param_size = 0;
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_NAME, param_size, nullptr, &param_size));

            std::vector<unsigned char> dev_name (param_size, 0);
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_NAME, param_size, dev_name.data(), &param_size));
            std::cout << "    Device name: " << dev_name.data() << std::endl;
            
            cl_device_type dev_type;
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &dev_type, &param_size));
            switch (dev_type)
            {
            case CL_DEVICE_TYPE_CPU:
                std::cout << "    Dev type :: CPU " << std::endl;
                break;
            case CL_DEVICE_TYPE_GPU:
                std::cout << "    Dev type :: GPU " << std::endl;
                break;
            default:
                std::cout << "    Dev type :: unknown " << std::endl;
                break;
            }

            cl_ulong glob_mem_size; //bytes
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &glob_mem_size, &param_size));
            std::cout << "   Global memory: " << glob_mem_size/(1024*1024) << "Mb" << std::endl;

            cl_ulong local_mem_size; //bytes
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &local_mem_size, &param_size));
            std::cout << "   Local memory: " << local_mem_size/(1024) << "K" << std::endl;

            selected_device = device;
            break;
        }
    }


    if (!selected_device) {
        cout << "Cannot find appropriate device!";
        return 0;
    }
    cout << "Selected device: " << selected_device << endl;


    cl_int err;
    cl_context context = clCreateContext(NULL, 1, &selected_device, NULL, NULL, &err);
    OCL_SAFE_CALL(err);

    cl_command_queue queue = clCreateCommandQueue(context, selected_device, 0, &err);
    OCL_SAFE_CALL(err);
    cout << "queue and context has been created" << endl;

    const char *filename = KERNEL_FILE_PATH;
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t source_size = ftell(file);
    rewind(file);

    char *source_str = (char*)malloc(source_size + 1);
    source_str[source_size] = '\0';
    fread(source_str, sizeof(char), source_size, file);
    fclose(file);

    // Create and build program
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &err);
    OCL_SAFE_CALL(err);

    err = clBuildProgram(program, 1, &selected_device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        // Determine the reason for the error
        char build_log[16384];
        clGetProgramBuildInfo(program, selected_device, CL_PROGRAM_BUILD_LOG, sizeof(build_log), build_log, NULL);
        fprintf(stderr, "Error in kernel: %s\n", build_log);
        exit(EXIT_FAILURE);
    }
    free(source_str);

    const int width = 4000;
    const int height = 2000;
    size_t buffer_size = width * height * sizeof(uchar);
    cl_mem image_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, buffer_size, NULL, &err);
    OCL_SAFE_CALL(err);

    cl_kernel kernel = clCreateKernel(program, "mandelbrot", &err);
    OCL_SAFE_CALL(err);

    float x0, x1, y0, y1;
    int maxIterations;

    x0 = -2;
    x1 = 1;
    y0 = -1;
    y1 = 1;
    maxIterations = 120;

    // Set kernel arguments
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &image_buffer);
    err |= clSetKernelArg(kernel, 1, sizeof(int), &width);
    err |= clSetKernelArg(kernel, 2, sizeof(int), &height);
    err |= clSetKernelArg(kernel, 3, sizeof(float), &x0);
    err |= clSetKernelArg(kernel, 4, sizeof(float), &y0);
    err |= clSetKernelArg(kernel, 5, sizeof(float), &x1);
    err |= clSetKernelArg(kernel, 6, sizeof(float), &y1);
    err |= clSetKernelArg(kernel, 7, sizeof(int), &maxIterations);
    OCL_SAFE_CALL(err);

    cout << "Starting kernel..." << endl;
    auto start = high_resolution_clock::now();
    size_t global_work_size[2] = {width, height};
    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
    OCL_SAFE_CALL(err);

    uchar *image = (uchar*)malloc(buffer_size);
    err = clEnqueueReadBuffer(queue, image_buffer, CL_TRUE, 0, buffer_size, image, 0, NULL, NULL);
    OCL_SAFE_CALL(err);
    auto stop = high_resolution_clock::now();
    cout << "Kernel finished" << endl;
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Kernel duration: " << duration.count() << "ms" << endl;

    write_to_ppm_ascii(image, width, height, "output.ppm");

    // Release OpenCL resources
    clReleaseMemObject(image_buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    free(image);

    return 0;
}
