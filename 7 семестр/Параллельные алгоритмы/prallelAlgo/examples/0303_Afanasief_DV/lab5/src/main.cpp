#include "mandelbrot.h"
#include <fstream>

int main() {
    float ratio = 5;
    const size_t width = 1920;
    const size_t height = 1280;
    int iterLimit = 1000;

    auto buffer = computeMandelbrot(height, width, ratio, iterLimit);
    const auto buffPointer = buffer.data();
    {
        std::ofstream file("mandelbrot.ppm", std::ios::binary);
        file << "P6\n" << width << " " << height << "\n255\n";

        for (unsigned int y = 0; y < height; ++y) {
            const unsigned int *row = buffPointer + width * y;

            for (unsigned int x = 0; x < width; ++x) {
                file.write((const char *) (row + x), 3);
            }

        }
        file.close();
    }
    return 0;
}
