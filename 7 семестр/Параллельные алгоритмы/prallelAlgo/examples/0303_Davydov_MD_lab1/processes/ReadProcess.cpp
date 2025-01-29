#include "ReadProcess.h"

const std::string A_MATRIX_FILENAME = "A_MATRIX.txt";
const std::string B_MATRIX_FILENAME = "B_MATRIX.txt";

ReadProcess::ReadProcess() 
{
    m_sharedMemory = new SharedMemory(READ);
    m_AMatrixFileName = A_MATRIX_FILENAME;
    m_BMatrixFileName = B_MATRIX_FILENAME;
}

ReadProcess::~ReadProcess() 
{
    delete m_sharedMemory;
}

void ReadProcess::run() 
{
    if (!m_sharedMemory->checkMemory()) 
    {
        classError(typeid(*this).name(), std::string("Memory error"));
        return;
    }

    m_sharedMemory->setProcessStatus(READ, RUN);

    try 
    {
        readMatrix(m_AMatrixFileName, A);
        readMatrix(m_BMatrixFileName, B);
    } 
    catch (std::runtime_error &exception) 
    {
        m_sharedMemory->crash();
        classError(typeid(*this).name(), exception.what());
    }

    if (m_sharedMemory->getMatrixWidth(A) != m_sharedMemory->getMatrixHeight(B)) 
    {
        m_sharedMemory->crash();
        classError(typeid(*this).name(), "Matrix A and matrix B are not compatible in size");
        throw std::runtime_error("Matrix A and matrix B are not compatible in size");
    }

    m_sharedMemory->setProcessStatus(READ, TERMINATE);
}

void ReadProcess::readMatrix(std::string fileName, matrix matrixName) 
{
    std::ifstream file(fileName);
    if (!file.is_open()) 
    {
        m_sharedMemory->crash();
        classError(typeid(*this).name(), "Invalid input file");
        throw std::runtime_error("Invalid input file");
    }

    int y = 0;
    double num;
    std::vector<double> matrixLine;
    size_t lineWidth = 0;
    
    while (file >> num) 
    {
        if (matrixLine.size() == MAX_MATRIX_SIZE) 
        {
            m_sharedMemory->crash();
            classError(typeid(*this).name(), "Input matrix sizes too large");
            throw std::runtime_error("Input matrix sizes too large");
        }
        matrixLine.push_back(num);
        
        if (file.peek() == (int)'\n') 
        {
            if (y == 0) 
            {
                lineWidth = matrixLine.size();
            } 
            else 
            {
                if (matrixLine.size() != lineWidth) 
                {
                    m_sharedMemory->crash();
                    classError(typeid(*this).name(), "Input data is not a matrix");
                    throw std::runtime_error("Input data is not a matrix");
                }
            }
            for (int x = 0; x < matrixLine.size(); x++) 
            {
                m_sharedMemory->setValue(matrixLine[x], matrixName, x, y);
            }
            y++;
            matrixLine.clear();
        }
    }
    for (int x = 0; x < matrixLine.size(); x++) 
    {
        m_sharedMemory->setValue(matrixLine[x], matrixName, x, y);
    }
    
    file.close();
}
