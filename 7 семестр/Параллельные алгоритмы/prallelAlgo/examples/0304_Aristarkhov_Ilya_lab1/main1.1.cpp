#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <random>

#include <fcntl.h>
#include <sys/un.h>
#include <sys/stat.h>

// Using square matrices. Must not be grater then 80!
//#define MATRIX_SIZE 5 // ~mean 275
//#define MATRIX_SIZE 10 // ~mean 281
//#define MATRIX_SIZE 20 // ~mean 341
//#define MATRIX_SIZE 40 // ~mean 649
#define MATRIX_SIZE 80 // ~mean 2439

struct generated_matrices {
    int matrix1[MATRIX_SIZE][MATRIX_SIZE];
    int matrix2[MATRIX_SIZE][MATRIX_SIZE];
};

struct calculated_matrix {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
};

generated_matrices generate_matrices();

calculated_matrix multiply_matrices(generated_matrices generatedMatrices);

void writeAnswer(std::string_view filePath, calculated_matrix calculatedMatrix);

int main() {
    using std::cout;
    using std::cin;
    using std::string;

    if (MATRIX_SIZE >= 81) {
        cout << "Matrix size is too grate. It must be lower the 81\n";
        std::exit(1);
    }

    const char *genToCalcPipe{"/var/lock/genToCalcPipe"};
    const char *calcToOutPipe{"/var/lock/calcToOutPipe"};

    const string outputPath{"./output.txt"};

    // Saving program start time
    auto start = std::chrono::high_resolution_clock::now();

    // Creating pipes for Gen -> Calc and Calc -> Out
    long retGen{mkfifo(genToCalcPipe, 0666)};
    if (retGen < 0)
        cout << "Error when creating FIFO for generator. " << strerror(errno) << "\n";

    long retCalc{mkfifo(calcToOutPipe, 0666)};
    if (retCalc < 0)
        cout << "Error when creating FIFO for calculator. " << strerror(errno) << "\n";


    // Forking main process
    pid_t pid = fork();

    if (pid != 0) {
        // This is a base process. It will used as last part to measure execution time of the whole app
        // ################# OUTPUT #################

        // Opening Calc -> Out pipe for reading
        int fdCalcToOut{open(calcToOutPipe, O_RDONLY)};

        // Receiving calculated matrix
        calculated_matrix received_message{};
        long statusRetGen = read(fdCalcToOut, &received_message, sizeof(received_message));
        if (statusRetGen < 0)
            printf("Error while reading generated matrices. %s\n", strerror(errno));

//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // Closing pipe
        close(fdCalcToOut);

        // Outputting answer to file
        writeAnswer(outputPath, received_message);

        // Calculating execution time
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
//        cout << "Duration: " << duration.count() << " microseconds\n";
        cout << duration.count() << "\n";
    } else {
        // Forking again
        pid_t pidFork = fork();

        if (pidFork != 0) {
            // ################# GENERATOR #################

            // Opening Gen -> Calc pipe for writing
            int fdGenToCalc{open(genToCalcPipe, O_WRONLY)};

            // Generating matrices
            auto message = generate_matrices();

            // Sending
            long statusRetGen = write(fdGenToCalc, &message, sizeof(message));
            if (statusRetGen < 0) {
                printf("Error while writing generated matrices. %s\n", strerror(errno));
            }

//            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // Closing pipe
            close(fdGenToCalc);
        } else {
            // ################# CALCULATOR #################
            // Opening Gen -> Calc pipe for reading
            int fdGenToCalc{open(genToCalcPipe, O_RDONLY)};
            // Opening Calc -> Out pipe for writing
            int fdCalcToOut{open(calcToOutPipe, O_WRONLY)};

            // Receiving generated matrices
            generated_matrices received_message{};

            long statusRetGen = read(fdGenToCalc, &received_message, sizeof(received_message));
            if (statusRetGen < 0)
                printf("Error while reading generated matrices. %s\n", strerror(errno));

//            std::this_thread::sleep_for(std::chrono::milliseconds(10));


            // Multiplying them
            auto message = multiply_matrices(received_message);

            // .. and sending to output
            statusRetGen = write(fdCalcToOut, &message, sizeof(message));
            if (statusRetGen < 0) {
                printf("Error while writing calculated matrix. %s\n", strerror(errno) );
            }

//            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            // Closing pipes
            close(fdGenToCalc);
            close(fdCalcToOut);
        }
    }

    // Removing pipes
    unlink(genToCalcPipe);
    unlink(calcToOutPipe);

    return 0;
}


generated_matrices generate_matrices() {
    generated_matrices matrices{};

    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution die100{ -100, 100 };

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrices.matrix1[i][j] = die100(mt);
            matrices.matrix2[i][j] = die100(mt);
        }
    }

    return matrices;
}

calculated_matrix multiply_matrices(generated_matrices generatedMatrices) {
    calculated_matrix result{};

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            int tmp = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                tmp += generatedMatrices.matrix1[i][k] * generatedMatrices.matrix2[k][j];
            }
            result.matrix[i][j] = tmp;
        }
    }

    return result;
}

void writeAnswer(std::string_view filePath, calculated_matrix calculatedMatrix) {

    std::ofstream outf{static_cast<std::string>(filePath)};

    if (!outf) {
        printf("Couldn't open output file for writing.\n");
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            outf << calculatedMatrix.matrix[i][j] << " ";
        }
        outf << "\n";
    }

    outf.close();
}