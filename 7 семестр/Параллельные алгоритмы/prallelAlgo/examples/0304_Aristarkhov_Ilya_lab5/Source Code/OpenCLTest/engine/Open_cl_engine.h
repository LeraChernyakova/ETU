#ifndef OPENCLTEST_OPEN_CL_ENGINE_H
#define OPENCLTEST_OPEN_CL_ENGINE_H

#include <string>

#include <CL/cl.h>
#include <sstream>

class Open_cl_engine {
private:
    cl_device_id device;

    cl_context ctx;
    cl_command_queue queue;
    cl_kernel kernel;

    cl_program program;

    cl_mem cl_img;


    cl_device_id get_device();

    void build(std::string source);

    template<typename T>
    std::string to_string(T value) {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }

public:

    void init();

    void output_platforms_data();

    void load_program(std::string source, std::string kernel_name);

    void create_img(size_t width, size_t height);

    void read_image(uint8_t* img, size_t width, size_t height);

    void execute_and_wait();

    void clean_up();

};


#endif //OPENCLTEST_OPEN_CL_ENGINE_H
