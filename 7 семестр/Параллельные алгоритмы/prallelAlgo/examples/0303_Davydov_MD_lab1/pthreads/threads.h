#ifndef THREADS_THREADS_H
#define THREADS_THREADS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <utility>
#include <string>

template<typename T>
using Matrix = std::vector<std::vector<T>>;

class Threads {
public:
    Threads(int);
    ~Threads() = default;
    void run();

private:
    static bool reading(Matrix<double> *, Matrix<double> *);
    static void readMatrix(Matrix<double> *, std::string);
    
    static bool calculation(Matrix<double> *, Matrix<double> *, Matrix<double> *, int);
    static void calculateMatrix(Matrix<double> *, Matrix<double> *, Matrix<double> *, int, int);
    static bool writing(Matrix<double> *);
    static void writeMatrix(Matrix<double> *);

    Matrix<double> m_matrixA;
    Matrix<double> m_matrixB;
    Matrix<double> m_matrixC;
    int m_threadsNum;
};

#endif //THREADS_THREADS_H
