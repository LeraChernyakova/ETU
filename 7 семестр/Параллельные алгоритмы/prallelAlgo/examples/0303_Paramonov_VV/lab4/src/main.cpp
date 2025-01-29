#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "utils/matrix.h"
#include "multiply/multiply.h"

using namespace std;
using namespace std::chrono;


int main() {
    // Количество разных размеров строк первой матрицы, с которыми перезапускать.
    int size = 8192;
    const int fRows = size;
    const int fCols = size;
    const int sRows = size;
    const int sCols = size;
    // Количество рестартов для получения усредненного результата.
    int numRestarts = 1;
    // Количество потоков обработки.
    int threadsNum = 7;

    cout << "Matrix multiplication methods:" << endl;
    cout << "1 - lab1 matrix multiplication (by rows)." << endl;
    cout << "2 - scalable matrix multiplication." << endl;
    cout << "3 - “fast” matrix multiplication (Strassen)." << endl;

    int startChoice = 1;
    int endChoice = 3;

    system_clock::time_point start[endChoice], end[endChoice];
    double sum_duration[endChoice] = {0, 0, 0};

    for (int i = 0; i < numRestarts; i++) {
        Matrix first(fRows, fCols, -5, 5);
        Matrix second(sRows, sCols, -5, 5);
        Matrix mulResult[endChoice];

        for (int choice = 0; choice < endChoice; choice++) {
            mulResult[choice] = Matrix(fRows, sCols);
        }

        // first.printMatrix();
        // second.printMatrix();
        
        vector<thread> mulThreads = vector<thread>(threadsNum);

        for (int choice = startChoice; choice < endChoice; choice++) {
            start[choice] = high_resolution_clock::now();
            if (choice != 2) {
                for (int threadInd=0; threadInd < threadsNum; threadInd++) {
                    if (choice == 0) {
                        mulThreads[threadInd] = thread(threadsMulLab1, 
                            ref(first), ref(second), ref(mulResult[choice]), threadInd, threadsNum);
                    } else if (choice == 1) {
                        mulThreads[threadInd] = thread(threadsScalableMul, 
                            ref(first), ref(second), ref(mulResult[choice]), threadInd, threadsNum);
                    }
                }

                
                for (int threadInd=0; threadInd < threadsNum; threadInd++) {
                    mulThreads[threadInd].join();
                }
            } else {
                int allowRecursionDepth = 3;
                if (first.getCols() != second.getCols() || first.getRows() != second.getRows() || first.getCols() != first.getRows()) {
                    cout << "The matrices must be square." << endl;
                    exit(1);
                }

                if ((first.getCols() % (1 << allowRecursionDepth)) != 0) {
                    cout << "The matrices must have sides divisible to 2^" <<  allowRecursionDepth << "." << endl;
                    exit(1);
                }

                mulThreads[0] = thread(threadsMulStrassen, first, second, ref(mulResult[choice]), 0, allowRecursionDepth);
                mulThreads[0].join();
            }
            end[choice] = high_resolution_clock::now();

            sum_duration[choice] += duration<double>(end[choice] - start[choice]).count();
        }

        // Проверим правильность вычислений 3 методами с помощью сравнения полученных матриц:
        bool equal = true;
        for (int choice = startChoice; choice < endChoice - 1; choice++) {
            if (!(mulResult[choice] == mulResult[choice + 1])) {
                equal = false;
            }
        }
        string path_res = "output/mul_res.txt";
        mulResult[0].writeMatrix(path_res);

        if (!equal) {
            cout << "An error occurred while calculating the result; \
                        the results obtained by different methods don't match." << endl;
            exit(1);
        }
    }

    for (int k = startChoice; k < endChoice; k++) {
        cout << "Time of " << k + 1 << " task with matrix size first=(" << fRows << "," << fCols << "); " 
                << "second=(" << sRows << ", " << sCols << ") and num of threads = " << threadsNum 
                    << ": "<< sum_duration[k] / numRestarts << endl;
    }
    return 0;
}