#include "additional.h"

void save_image(const cl_uint* pix, int w, int h, const char* fileName) {
    std::ofstream file(fileName, std::ios::binary);
    file << "P6\n" << w << " " << h << "\n255\n";
    for (int y = 0; y < h; y++) {
        const cl_uint* line = pix + w * y;
        for (int x = 0; x < w; x++) {
            file.write((const char*)(line + x), 3);
        }
    }
}

int align(int x, int y) { // сделать кратным число
    return (x + y - 1) / y * y;
}