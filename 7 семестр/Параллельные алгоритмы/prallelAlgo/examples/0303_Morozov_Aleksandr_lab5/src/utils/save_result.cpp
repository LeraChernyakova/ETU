#include "../include/utils.hpp"


void save_result(const cl_uint* pixels, int w, int h) {
    std::ofstream file("result.ppm", std::ios::binary);
    file << "P6\n" << w << " " << h << "\n255\n";
    for (int y = 0; y < h; y++) {
        const cl_uint* line = pixels + w * y;
        for (int x = 0; x < w; x++) {
            file.write((const char*)(line + x), 3);
        }
    }
}