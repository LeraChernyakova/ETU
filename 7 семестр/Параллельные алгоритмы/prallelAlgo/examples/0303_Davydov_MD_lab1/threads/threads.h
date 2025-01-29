#ifndef THREADS_THREADS_H
#define THREADS_THREADS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>

enum status {
    START,
    READY,
    RUN,
    TERMINATE
};

template<typename T>
using Matrix = std::vector<std::vector<double>>;

class Threads 
{
public:
    Threads();
    void run();

private:
    static void reading(Matrix<double> *, Matrix<double> *, status *, bool *);
    static void readMatrix(Matrix<double> *, std::string);

    static void calculation(Matrix<double> *, Matrix<double> *, Matrix<double> *, status *, status *, bool *);
    static void calculateMatrix(Matrix<double> *, Matrix<double> *, Matrix<double> *, bool *);

    static void writing(Matrix<double> *, status *, status *, bool *);
    static void writeMatrix(Matrix<double> *, status *, bool *);
private:
    Matrix<double> m_matrixA;
    Matrix<double> m_matrixB;
    Matrix<double> m_matrixC;
    status m_readingStatus;
    status m_calculatingStatus;
    status m_writingStatus;
    bool m_isCrash;
};

#endif //THREADS_THREADS_H
