#ifndef OPENCLTEST_OPEN_CL_ENGINE_H
#define OPENCLTEST_OPEN_CL_ENGINE_H

#include <string>

#include <CL/cl.h>
#include <sstream>

class Open_cl_engine {
private:
    cl_device_id device;

    cl_context ctx = nullptr;
    cl_command_queue queue = nullptr;
    cl_kernel kernel = nullptr;

    cl_program program = nullptr;

    cl_mem first_buffer = nullptr;
    cl_mem second_buffer = nullptr;
    cl_mem result_buffer = nullptr;


    auto get_device() -> cl_device_id;

    void build(std::string source);

    template<typename T>
    static auto to_string(T value) -> std::string {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }

public:

    void init();

    void load_program(std::string source, std::string kernel_name);

    void create_buffers(size_t size, std::vector<int>& first_buffer_data, std::vector<int>& second_buffer_data);

    void read_buffer(int* result, size_t size);

    void execute_and_wait();

    void clean_up();

};


#endif //OPENCLTEST_OPEN_CL_ENGINE_H
