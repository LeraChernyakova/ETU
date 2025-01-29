#include <iostream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include "engine.h"
#include "matrix.h"
#include "threading.h"

#define EXPERIMENTS_AMOUNT 10
#define MATRIX_SIZE 2048
#define WORK_GROUP_WIDTH 32
#define WORK_GROUP_HEIGHT 32

void performExperiment(std::vector<long long> &durations, size_t experimentIndex) {
    // Initialize OpenCl custom engine
    OpenCLEngine engine{};
    engine.init();

    // Reading .cl source code
    std::ifstream f("../multiply.cl");
    std::stringstream buf;
    buf << f.rdbuf();
    std::string source_code{buf.str()};

    // Building program and creating kernel for it
    engine.load_program(source_code, "multiply");

    Matrix leftMatrix(MATRIX_SIZE);
    Matrix rightMatrix(MATRIX_SIZE);
    Matrix resultMatrix(MATRIX_SIZE);

    int *result_buffer_data = new int[MATRIX_SIZE * MATRIX_SIZE];
    std::vector<int> first_buffer_data(MATRIX_SIZE * MATRIX_SIZE);
    std::vector<int> second_buffer_data(MATRIX_SIZE * MATRIX_SIZE);

    // Timer
    auto startTime = std::chrono::high_resolution_clock::now();

    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution die100{-100, 100};


    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            int firstData = die100(mt);
            int secondData = die100(mt);

            first_buffer_data[i * MATRIX_SIZE + j] = firstData;
            leftMatrix.set_value(firstData, i, j);

            second_buffer_data[i * MATRIX_SIZE + j] = secondData;
            rightMatrix.set_value(secondData, i, j);
        }
    }

    engine.create_buffers(MATRIX_SIZE, first_buffer_data, second_buffer_data, WORK_GROUP_WIDTH, WORK_GROUP_HEIGHT);
    engine.read_buffer(result_buffer_data, MATRIX_SIZE);
    engine.execute_and_wait();

    // Timer
    auto finishTime = std::chrono::high_resolution_clock::now(); // ---
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
    durations[experimentIndex] = duration.count();

    // Log experiment results
    log("Experiment #" + std::to_string(experimentIndex + 1) + ": "
    + std::to_string(durations[experimentIndex]) + " microseconds.");

    // Cleaning up (closing kernel, program, image variable, queue and context)
    engine.clean_up();

    // Removing image byte array
    delete[] result_buffer_data;
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
