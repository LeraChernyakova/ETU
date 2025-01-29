#include "opencl/opencl.hpp"
#include "Matrix.hpp"
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

void fillBuffers(int matricesSize, vector<int> &firstBufferData, vector<int> &secondBufferData) {
    Matrix leftMatrix(matricesSize, matricesSize);
    Matrix rightMatrix(matricesSize, matricesSize);
    leftMatrix.fillMatrix();
    rightMatrix.fillMatrix();
    int index = 0;
    for (int i1 = 0; i1 < matricesSize; ++i1) {
        for (int j1 = 0; j1 < matricesSize; ++j1) {
            firstBufferData[index] = leftMatrix.data[i1][j1];
            secondBufferData[index] = rightMatrix.data[i1][j1];
            index++;
        }
    }
}

void makeExperiment(OpenCl &opencl, vector<int> &firstBufferData, vector<int> &secondBufferData, int matricesSize, int workGroupSize) {
    opencl.createBuffers(matricesSize, firstBufferData, secondBufferData, workGroupSize);
    opencl.startAndWait();
}

int main() {
    auto opencl = OpenCl();
    opencl.init();

    std::ifstream file("../multiply_matrices.cl");
    std::stringstream programBuffer;
    programBuffer << file.rdbuf();
    std::string sourceClCode = programBuffer.str();

    opencl.loadProgram(sourceClCode, "multiply_matrices");
    vector<int> matricesSizes = {128, 256, 512, 1024, 2048};
    vector<int> workGroupSizes = {8, 16, 32};
    int amountOfExperiments = 10;

    for (int i = 0; i < matricesSizes.size(); ++i) {
        for (int j = 0; j < workGroupSizes.size(); ++j) {
            int matricesSize = matricesSizes[i];
            int workGroupSize = workGroupSizes[j];
            vector<long> durations;
            for (int experiment = 1; experiment <= amountOfExperiments; ++experiment) {
                vector<int> firstBufferData(matricesSize * matricesSize);
                vector<int> secondBufferData(matricesSize * matricesSize);
                vector<int> resultBufferData(matricesSize * matricesSize);
                fillBuffers(matricesSize, firstBufferData, secondBufferData);

                auto startTime = std::chrono::high_resolution_clock::now();
                makeExperiment(opencl, firstBufferData, secondBufferData, matricesSize, workGroupSize);
                auto finishTime = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime);
                durations.push_back(duration.count());
            }
            long long average = 0;
            for (int k = 0; k < durations.size(); ++k) {
                average += durations[i];
            }
            average /= durations.size();
            std::cout << "for " << matricesSize << "x" << matricesSize << " and " << workGroupSize << "x" << workGroupSize << ": average time = " << average << " microseconds\n";
        }
    }

    opencl.destroy();
    return 0;
}


