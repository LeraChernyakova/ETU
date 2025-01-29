#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

#include "tasks.h"
#include "../utils/matrix.h"

using namespace std;


int processesStageSep(int fRows, int fCols, int sRows, int sCols, string& outFileName, bool printToConsole) {
    int fd[3][2];

    // Открываем каналы.
    for (int i=0; i < 3; i++) {
        if (pipe(fd[i]) < 0) {
            // Если ошибка, то закрываем открытые дескрипторы и выходим.
            for (int j=0; j < i; j++) {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            return 1;
        }
    }

    pid_t pidCreate, pidMultiply;
    switch(pidCreate=fork()) {
        case -1: {
            // Ошибка fork, закрываем дескрипторы и выходим.
            for (int i=0; i < 3; i++) {
                close(fd[i][0]);
                close(fd[i][1]);
            }
            return 2; 
        }
        case 0: {
            // Первый ребенок.
            // Инициализация матриц.
            close(fd[0][0]);
            close(fd[1][0]);
            close(fd[2][0]);
            close(fd[2][1]);

            if (printToConsole) 
                cout << "Create process." << endl;

            Matrix first(fRows, fCols, -20, 20);
            Matrix second(sRows, sCols, -20, 20);
            int* fBuf = first.serialize();
            int* sBuf = second.serialize();
            if (printToConsole) {
                cout << "First matrix:" << endl;
                first.printMatrix();
                cout << "Second matrix:" << endl;
                second.printMatrix();
            }

            write(fd[0][1], fBuf, sizeof(int) * fRows * fCols);
            write(fd[1][1], sBuf, sizeof(int) * sRows * sCols);

            delete[] fBuf;
            delete[] sBuf;

            close(fd[0][1]);
            close(fd[1][1]);
            exit(0);
        }
        default: {
            switch(pidMultiply=fork()) {
                case -1: {
                    // Ошибка fork, закрываем дескрипторы и выходим.
                    for (int i=0; i < 3; i++) {
                        close(fd[i][0]);
                        close(fd[i][1]);
                    }
                    return 2; 
                }
                case 0: {
                    // Второй ребенок.
                    // Умножение матриц.
                    close(fd[0][1]);
                    close(fd[1][1]);
                    close(fd[2][0]);

                    int* fBuf = new int[fRows * fCols];
                    int* sBuf = new int[sRows * sCols];
                    read(fd[0][0], fBuf, sizeof(int) * fRows * fCols);
                    read(fd[1][0], sBuf, sizeof(int) * sRows * sCols);

                    Matrix first(fRows, fCols);
                    Matrix second(sRows, sCols);
                    first.deserialize(fBuf);
                    second.deserialize(sBuf);

                    if (printToConsole)
                        cout << "Multiply process." << endl;
                    Matrix mulResult(fRows, sCols);
                    vector<int> computedRow; 
                    for (int fRow=0; fRow < fRows; fRow++) {
                        computedRow = first.multiplyRow(first, second, fRow);
                        mulResult.setRow(fRow, computedRow);
                    }

                    int* resultBuf = mulResult.serialize();
                    write(fd[2][1], resultBuf, sizeof(int) * fRows * sCols);

                    delete[] fBuf;
                    delete[] sBuf;
                    delete[] resultBuf;

                    close(fd[0][0]);
                    close(fd[1][0]);
                    close(fd[2][1]);
                    exit(0);
                }
                default: {
                    // Родитель.
                    // Вывод матриц.
                    close(fd[0][0]);
                    close(fd[0][1]);
                    close(fd[1][0]);
                    close(fd[1][1]);
                    close(fd[2][1]);

                    Matrix mulResult(fRows, sCols);
                    int* resultBuf = new int[fRows * sCols];
                    read(fd[2][0], resultBuf, sizeof(int) * fRows * sCols);

                    if (printToConsole)
                        cout << "Output process." << endl;
                    mulResult.deserialize(resultBuf);
                    mulResult.writeMatrix(outFileName);

                    if (printToConsole) {
                        cout << "Multiplication result matrix:" << endl;
                        mulResult.printMatrix();
                    }

                    delete[] resultBuf;

                    close(fd[2][0]);

                    wait(&pidCreate);
                    wait(&pidMultiply);
                }
            }
        }
    }
    return 0;
}