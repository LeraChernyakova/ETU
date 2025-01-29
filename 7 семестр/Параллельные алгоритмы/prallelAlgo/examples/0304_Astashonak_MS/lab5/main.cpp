#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>
#include "utils.h"
#include "engine.h"
#include "svpng.h"

#define EXPERIMENTS_AMOUNT 10
#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024
#define WORK_GROUP_WIDTH 1
#define WORK_GROUP_HEIGHT 1
#define FRACTAL_DEPTH 256
#define STRICT_CPU false

void performExperiment(std::vector<long long> &durations, size_t experimentIndex) {
    // Initialize OpenCl custom engine
    OpenCLEngine engine{};
    engine.init(STRICT_CPU);

    // Reading .cl source code
    std::ifstream f("../mandelbrot.cl");
    std::stringstream buf;
    buf << f.rdbuf();
    std::string source_code{buf.str()};


    // Building program and creating kernel for it
    engine.load_program(source_code, "mandelbrot");

    // Timer
    auto startTime = std::chrono::high_resolution_clock::now();

    // Creating img argument for program and loading it into the kernel
    engine.create_img(IMAGE_WIDTH, IMAGE_HEIGHT, WORK_GROUP_WIDTH, WORK_GROUP_HEIGHT, FRACTAL_DEPTH);

    // Creating var for image read and creating read task in queue
    auto *image = new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * 4];
    engine.read_image(image, IMAGE_WIDTH, IMAGE_HEIGHT);

    // Flushing queue and wait for completion
    engine.execute_and_wait();

    // Timer
    auto finishTime = std::chrono::high_resolution_clock::now(); // ---
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
    durations[experimentIndex] = duration.count();

    // Log experiment results
    log("Experiment #" + std::to_string(experimentIndex + 1) + ": "
    + std::to_string(durations[experimentIndex]) + " microseconds.");

    // Creating png file
    FILE* fp = fopen("../result.png", "wb");
    svpng(fp, IMAGE_WIDTH, IMAGE_HEIGHT, image, 1);
    fclose(fp);

    // Cleaning up (closing kernel, program, image variable, queue and context)
    engine.clean_up();

    // Removing image byte array
    delete[] image;
}


int main(int argc, char *argv[]) {
    log("Experiments started.");
    std::vector<long long> durations(EXPERIMENTS_AMOUNT);

    // Iterate over experiments
    for (size_t experiment_index = 0; experiment_index < EXPERIMENTS_AMOUNT; experiment_index++)
        performExperiment(durations, experiment_index);

    log("Experiments finished.");

    // Log mean value
    auto meanDuration = std::accumulate(durations.begin(),durations.end(),(long long)0) / EXPERIMENTS_AMOUNT;
    log("Mean experiment duration (in " + std::to_string(EXPERIMENTS_AMOUNT) + " experiments): "
        + std::to_string(meanDuration) + " microseconds.");
}
