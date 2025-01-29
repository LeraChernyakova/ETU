#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>

#define REAL_PARALLEL

void generate_matrices(int size, int** matrix1, int** matrix2);

void multiply_matrices_thr(int** matrix1, int** matrix2,
                           int** resultMatrix, int iStart, int jStart, int iFinish, int jFinish, int matrixSize);

void multiply_matrices(int** matrix1, int** matrix2, int** resultMatrix, int matrixSize);

void writeAnswer(std::string_view filePath, int** matrix, int matrixSize);

consteval int checkThreadCount(const int threadsCount, const int matrixSize) {
    if (threadsCount > matrixSize * matrixSize) {
        return matrixSize * matrixSize;
    }
    else return threadsCount;
}

int main(int argc, char **argv) {

    using std::cout;
//    using std::vector;
    using std::string;
    using std::thread;

    const string outputFilePath = "./output";
    /*
     * 1: 169
     * 5: 156
     * 10: 168
     * 20: 226
     * 40: 547
     * 80: 2338
     * */
//    int matrixSize = std::stoi(argv[1]);
    int matrixSize = 400;

    /*

     * __40__
     * 1:       527 // Normal
     * 2:       539 // Check non 1 thread
     * 7:       620 // Check with all physical threads available
     * 15:      783 // Check double the physical number of threads
     * 40:      1282 // Check on matrix size
     * 1600:    43010 // Check on matrix^2
     * __400__
     * 1:       210758 // Normal
     * 2:       210193 // Check non 1 thread
     * 7:       208407 // Check with all physical threads available
     * 15:      205169 // Check double the physical number of threads
     * 400:     77042 // Check on matrix size
     * 1000:    92868
     */
    int threadsCount = std::stoi(argv[1]);


//    unsigned long const hardwareThreads = std::thread::hardware_concurrency();
//    std::cout << "This system has " << hardwareThreads << " threads\n";

    auto start = std::chrono::high_resolution_clock::now();

    // Initialising matrices
    int** matrix1 = new int*[matrixSize];
    int** matrix2 = new int*[matrixSize];
    int** resultMatrix = new int*[matrixSize];

    for (int i = 0; i < matrixSize; ++i) {
        matrix1[i] = new int[matrixSize];
        matrix2[i] = new int[matrixSize];
        resultMatrix[i] = new int[matrixSize];
        for (int j = 0; j < matrixSize; ++j) {
            matrix1[i][j] = 0;
            matrix2[i][j] = 0;
            resultMatrix[i][j] = 0;
        }
    }


    thread generatorThread(
            generate_matrices,
            matrixSize,
            matrix1,
            matrix2
    );

    generatorThread.join();

#ifdef REAL_PARALLEL
    int step = matrixSize * matrixSize / threadsCount;

    std::vector<std::thread> threads(threadsCount - 1);

    int iStart = 0;
    int jStart = 0;

    for (int i = 0; i < threadsCount - 1; ++i) {
        int iFinish = iStart;
        int jFinish = jStart + step;
        if (jFinish >= matrixSize) {
            iFinish++;

            jFinish = jFinish % matrixSize;
        }

        threads[i] = thread(multiply_matrices_thr, matrix1, matrix2, resultMatrix, iStart, jStart, iFinish, jFinish, matrixSize);

        iStart = iFinish;
        jStart = jFinish;
    }

    multiply_matrices_thr(matrix1, matrix2, resultMatrix, iStart, jStart, matrixSize-1, matrixSize-1, matrixSize);

    for (auto& entry: threads) {
        entry.join();
    }
#else
    thread calculatorThread(
            multiply_matrices,
            matrix1,
            matrix2,
            resultMatrix,
            matrixSize
    );

    calculatorThread.join();
#endif

    writeAnswer(outputFilePath, resultMatrix,
                matrixSize);

    for (int i = 0; i < matrixSize; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
        delete[] resultMatrix[i];
    }

    delete[] matrix1;
    delete[] matrix2;
    delete[] resultMatrix;

    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    cout << duration.count() << "\n";

    return 0;
}


void generate_matrices(int size, int** matrix1, int** matrix2) {
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution die100{-100, 100};

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix1[i][j] = die100(mt);
            matrix2[i][j] = die100(mt);
        }
    }
}

void multiply_matrices_thr(int** matrix1, int** matrix2,
                           int** resultMatrix, int iStart, int jStart, int iFinish, int jFinish, int matrixSize) {

    if (iStart == iFinish) {
        for (int j = jStart; j <= jFinish; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrixSize; ++k) {
                tmp += matrix1[iStart][k] * matrix2[k][j];
            }
            resultMatrix[iStart][j] = tmp;
        }
    } else {
        for (int j = jStart; j < matrixSize; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrixSize; ++k) {
                tmp += matrix1[iStart][k] * matrix2[k][j];
            }
            resultMatrix[iStart][j] = tmp;
        }
        for (int i = iStart + 1; i < iFinish; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                int tmp = 0;
                for (int k = 0; k < matrixSize; ++k) {
                    tmp += matrix1[i][k] * matrix2[k][j];
                }
                resultMatrix[i][j] = tmp;
            }
        }

        for (int j = 0; j <= jFinish; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrixSize; ++k) {
                tmp += matrix1[iFinish][k] * matrix2[k][j];
            }
            resultMatrix[iFinish][j] = tmp;
        }
    }




}

void multiply_matrices(int** matrix1, int** matrix2,
                       int** resultMatrix, int matrixSize) {

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            int tmp = 0;
            for (int k = 0; k < matrixSize; ++k) {
                tmp += matrix1[i][k] * matrix2[k][j];
            }
            resultMatrix[i][j] = tmp;
        }
    }

}

void writeAnswer(std::string_view filePath, int** matrix, int matrixSize) {

    std::ofstream outf{static_cast<std::string>(filePath)};

    if (!outf) {
        printf("Couldn't open output file for writing.\n");
    }

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            outf << matrix[i][j] << " ";
        }
        outf << "\n";
    }

    outf.close();
}