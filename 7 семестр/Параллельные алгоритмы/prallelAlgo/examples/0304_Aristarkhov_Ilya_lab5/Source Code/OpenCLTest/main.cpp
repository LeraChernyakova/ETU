#include <iostream>
#include <fstream>
#include <chrono>

#include "engine/Open_cl_engine.h"
#include "png/svgpng.hpp"


int main() {

    const size_t width = 1600;
    const size_t height = 800;

    Open_cl_engine engine{};

    // Getting device, creating context and command queue
    engine.init();

    // Reading .cl source code
    std::ifstream f("../mandelbrot.cl");
    std::stringstream buf;
    buf << f.rdbuf();
    std::string source_code{buf.str()};

    // Building program and creating kernel for it
    engine.load_program(source_code, "mandelbrot");

    auto start = std::chrono::high_resolution_clock::now();
    // Creating img argument for program and loading it into the kernel
    // Also enqueuing kernel work??
    engine.create_img(width, height);

    // Creating var for image read and creating read task in queue
    auto *image = new uint8_t[width * height * 4];
    engine.read_image(image, width, height);

    // Flushing queue and wait for completion
    engine.execute_and_wait();
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    std::cout << duration.count() << std::endl;

    // Creating png file
    FILE* fp = fopen("result.png", "wb");
    svpng(fp, width, height, image, 1);
    fclose(fp);


    // Cleaning up (closing kernel, program, img_variable, queue and context)
    engine.clean_up();
    // Removing image byte array
    delete[] image;
}
