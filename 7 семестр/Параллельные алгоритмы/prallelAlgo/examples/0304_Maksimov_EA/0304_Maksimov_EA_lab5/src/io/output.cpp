#include "output.h"

static std::ofstream fout;

bool openOutputFile(std::string fileName) {
    fout = std::ofstream(fileName, std::ios::binary);
    if(!fout) {
        std::cout << "Cannot open file " << fileName << " to write result.";
        return false;
    }

    return true;
}

void writeResult(const cl_uint* pixels, int width, int height) {
    fout << "P6\n" << width << " " << height << "\n255\n";      // PPM file header
    for(int y = 0; y < height; y++) {
        const cl_uint* line = pixels + width*y;
        for(int x = 0; x < width; x++) {
            fout.write((const char*)(line + x), 3);             // null characters too
        }
    }
    return;
}

void closeOutputFile() {
    fout.close();
    return;
}
