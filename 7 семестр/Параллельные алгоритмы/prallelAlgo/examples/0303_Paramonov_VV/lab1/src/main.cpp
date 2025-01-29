#include <iostream>
#include <chrono>

#include "tasks/tasks.h"

using namespace std;
using namespace std::chrono;


int main() {
    int choice;
    // Количество разных размеров строк первой матрицы, с которыми перезапускать.
    int fRowsStart = 120, fRowsEnd = 121;
    int fCols = 128;
    int sRows = 128;
    int sCols = 128;
    // Количество рестартов для получения усредненного результата.
    int numRestarts = 1;

    int threadsNum = 12;
    // Писать ли в консоль информацию о матрицах в ходе выполнения 1, 2 или 3.
    bool printToConsole = false;
    string outFileName = "output/out_mat.txt";

    cout << "Select matrix multiplication method:" << endl;
    cout << "1 - separation of calculation, input, output operations into separate processes." << endl;
    cout << "2 - separation of calculation, input, output operations into separate threads." << endl;
    cout << "3 - division of calculations into the number of threads by the number of rows of the first matrix." << endl;

    cin >> choice;

    int returnCode = 0;
    for (int fRows=fRowsStart; fRows < fRowsEnd; fRows++) {
        system_clock::time_point start, end;
        unsigned long sum_duration = 0;
        for (int i = 0; i < numRestarts; i++) {
            switch (choice) {
                case 1:
                    start = high_resolution_clock::now();
                    returnCode = processesStageSep(fRows, fCols, sRows, sCols, outFileName, printToConsole);
                    end = high_resolution_clock::now();
                    break;

                case 2:
                    start = high_resolution_clock::now();
                    returnCode = threadsStageSep(fRows, fCols, sRows, sCols, outFileName, printToConsole);
                    end = high_resolution_clock::now();
                    break;
                    
                case 3:
                    start = high_resolution_clock::now();
                    returnCode = threadsMultiply(fRows, fCols, sRows, sCols, outFileName, printToConsole, threadsNum);
                    end = high_resolution_clock::now();
                    break;
            }
            sum_duration += duration_cast<microseconds>(end - start).count();
        }
        if (choice < 3) {
            cout << "Time of " << choice << " task with matrix size first=(" << fRows << "," << fCols << "); " 
                << "second=(" << sRows << ", " << sCols << "): " << sum_duration / numRestarts << endl;
        } else {
            cout << "Time of " << choice << " task with matrix size first=(" << fRows << "," << fCols << "); " 
                    << "second=(" << sRows << ", " << sCols << ") and num of threads = " << threadsNum 
                        << ": "<< sum_duration / numRestarts << endl;
        }
    }
    return returnCode;
}