#include "ppmHelper.hpp"
#include "opencl/opencl.hpp"
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

int main() {
/*    const int width = 1600;
    const int height = 1600;*/

    auto opencl = OpenCl();
    opencl.init();

    std::ifstream file("../draw_mandelbrot.cl");
    std::stringstream programBuffer;
    programBuffer << file.rdbuf();
    std::string sourceClCode = programBuffer.str();

    opencl.loadProgram(sourceClCode, "draw_mandelbrot");
    vector<int> imageSizes = {256, 512, 1024, 2048};
    vector<int> workGroupSizes = {1, 4, 8, 16};

    for (int i = 0; i < imageSizes.size(); ++i) {
        for (int j = 0; j < workGroupSizes.size(); ++j) {
            int imageSize = imageSizes[i];
            int workGroupSize = workGroupSizes[j];

            auto startTime = std::chrono::high_resolution_clock::now();
            opencl.createImage(imageSize, imageSize, workGroupSize);
            auto *currentImage = new uint8_t[imageSize * imageSize * 4];
            opencl.readImage(currentImage, imageSize, imageSize);

            opencl.startAndWait();

            auto finishTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
            std::cout << "for " << imageSize << "x" << imageSize << " and " << workGroupSize << "x" << workGroupSize << ": " << duration.count() << "\n";
        }
    }

    int lastImageSize = imageSizes[imageSizes.size() - 1];
    int lastWorkGroupSize = workGroupSizes[workGroupSizes.size() - 1];
    opencl.createImage(lastImageSize, lastImageSize, lastWorkGroupSize);
    auto *currentImage = new uint8_t[lastImageSize * lastImageSize * 4];
    opencl.readImage(currentImage, lastImageSize, lastImageSize);
    opencl.startAndWait();
    auto outputImage = PpmImage(lastImageSize, lastImageSize);
    int currentIndex = 0;
    for (int i = 0; i < lastImageSize; ++i) {
        for (int j = 0; j < lastImageSize; ++j) {
            auto pixel = PpmPixel(currentImage[currentIndex], currentImage[currentIndex + 1], currentImage[currentIndex + 2]);
            outputImage.data[i][j] = pixel;
            currentIndex += 4;
        }
    }
    PpmHelper::save_image("output.ppm", outputImage);

    opencl.destroy();
    delete[] currentImage;
    return 0;
}
