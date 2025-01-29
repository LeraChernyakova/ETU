#include <CL/cl.h>
#include <libclew/ocl_init.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include "mandelbrot_computer.h"

#define TEST



void mandelbrotComputingTest(size_t height, size_t width, float ratio, size_t iterLimit){
    MandelbrotComputer mandelbrot(height, width, ratio, iterLimit);
}

inline void increaseParameters(size_t& height, size_t& width, size_t& iterLimit){
    height *= 1.5;
    width *= 1.5;
    iterLimit += 0;
}
inline void showResults(size_t& height, size_t& width, size_t& iterLimit, std::chrono::duration<double> time){
    std::cout << "Разрешение: " << width << " x " << height 
        << "\nМакс. итераций: " << iterLimit
        << "\nВремя: " << time.count() << " s."
        << "\nКол-во пикселей: " << width * height << "\n\n";
} 
int main(){
#ifdef TEST
    size_t width = 1920;
    size_t height = 1080;
    size_t iterLimit = 100;
    int counter = 7;
    while (counter-- > 0)
    {   
        auto start = std::chrono::high_resolution_clock::now();
        mandelbrotComputingTest(height, width, 3.5, iterLimit);
        auto end = std::chrono::high_resolution_clock::now();
        showResults(height, width, iterLimit, std::chrono::duration_cast<std::chrono::duration<double>>(end - start));
        increaseParameters(width, height, iterLimit);
    }
#else
    float ratio = 3.5;
    const size_t width = 19200;
    const size_t height = 10800;
    int iterLimit = 100;
    MandelbrotComputer mandelbrot(height, width, ratio, iterLimit);
    if(mandelbrot.isError()) return -1;
    auto buffer = mandelbrot.get();
    const auto buffPointer = buffer.data();
    {
        std::ofstream file("/home/igor/Code/c++Tasks/lb5/result/mandelbrot.ppm", std::ios::binary);
        file << "P6\n" << width << " " << height << "\n" << 1 << 24 <<"\n";

        for (auto y = 0; y < height; ++y) {
            const unsigned *row = buffPointer + width * y;

            for (auto x = 0; x < width; ++x) {
                file.write((const char *) (row + x), 3);
            }

        }
        file.close();
    }
#endif
    return 0;
}