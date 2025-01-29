#include "SharedMemory.h"

SharedMemory::SharedMemory(process proc) 
    : m_currentProcess(proc) 
{
    m_memoryBlockID = shmget(SHMID, sizeof(MemoryBlock), PERMS | IPC_CREAT);
    m_memoryBlock = (MemoryBlock*)shmat(m_memoryBlockID, nullptr, 0);
}

SharedMemory::~SharedMemory() 
{
    shmdt(m_memoryBlock);
    if (m_currentProcess == READ)
    {
        if (shmctl(m_memoryBlockID, IPC_RMID, nullptr) < 0)
        {
            classError(typeid(*this).name(), std::string("Remove memory"));
            throw std::runtime_error("Remove memory");
        }
    }
}

bool SharedMemory::checkMemory() const 
{
    return m_memoryBlockID >= 0 && m_memoryBlock != nullptr;
}

void SharedMemory::setProcessStatus(process proc, status stat) 
{
    if (proc != READ && proc != CALCULATE && proc != WRITE) 
    {
    	classError(typeid(*this).name(), std::string("Wrong proc_name"));
        throw std::runtime_error("Wrong process name");
    }

    switch (proc) 
    {
        case READ:
            m_memoryBlock->readingProcessStatus = stat;
            break;
        case CALCULATE:
            m_memoryBlock->calculationProcessStatus = stat;
            break;
        case WRITE:
            m_memoryBlock->writingProcessStatus = stat;
            break;
    }
}

status SharedMemory::getProcessStatus(process proc) const 
{
    if (proc != READ && proc != CALCULATE && proc != WRITE) 
    {
    	classError(typeid(*this).name(), std::string("Wrong proc_name"));
        throw std::runtime_error("Wrong proc_name");
    }

    switch (proc) 
    {
        case READ:
            return m_memoryBlock->readingProcessStatus;
        case CALCULATE:
            return m_memoryBlock->calculationProcessStatus;
        case WRITE:
            return m_memoryBlock->writingProcessStatus;
    }
}

void SharedMemory::crash() 
{
    m_memoryBlock->isCrash = true;
}

bool SharedMemory::isCrash() const 
{
    return m_memoryBlock->isCrash;
}

void SharedMemory::setValue(double value, matrix matrixName, int x, int y) 
{
    if (x < 0 || x >= MAX_MATRIX_SIZE || y < 0 || y >= MAX_MATRIX_SIZE) 
    {
    	classError(typeid(*this).name(), std::string("Coordinates are failed"));
        throw std::runtime_error("Coordinates are failed");
    }

    Matrix<double> *matrixPointer;
    switch (matrixName) 
    {
        case A:
            matrixPointer = &m_memoryBlock->matrixA;
            break;
        case B:
            matrixPointer = &m_memoryBlock->matrixB;
            break;
        case C:
            matrixPointer = &m_memoryBlock->matrixC;
            break;
    }

    matrixPointer->data[y][x] = value;
    if (x >= matrixPointer->width) 
    {
        matrixPointer->width = x + 1;
    }
    if (y >= matrixPointer->height) 
    {
        matrixPointer->height = y + 1;
    }
}

double SharedMemory::getValue(matrix matrixName, int x, int y) const 
{
    if (x < 0 || x >= MAX_MATRIX_SIZE || y < 0 || y >= MAX_MATRIX_SIZE) 
    {
    	classError(typeid(*this).name(), std::string("Coordinates are failed"));
        throw std::runtime_error("Coordinates are failed");
    }

    Matrix<double> *matrixPointer;
    switch (matrixName) 
    {
        case A:
            matrixPointer = &m_memoryBlock->matrixA;
            break;
        case B:
            matrixPointer = &m_memoryBlock->matrixB;
            break;
        case C:
            matrixPointer = &m_memoryBlock->matrixC;
            break;
    }

    return matrixPointer->data[y][x];
}

int SharedMemory::getMatrixHeight(matrix matrixName) const 
{
    if (matrixName != A && matrixName != B && matrixName != C) 
    {
    	classError(typeid(*this).name(), std::string("Noname matrix"));
        throw std::runtime_error("Noname matrix");
    }

    switch (matrixName) 
    {
        case A:
            return m_memoryBlock->matrixA.height;
        case B:
            return m_memoryBlock->matrixB.height;
        case C:
            return m_memoryBlock->matrixC.height;
    }
}

int SharedMemory::getMatrixWidth(matrix matrixName) const 
{
    if (matrixName != A && matrixName != B && matrixName != C) 
    {
    	classError(typeid(*this).name(), std::string("Noname matrix"));
        throw std::runtime_error("Noname matrix");
    }

    switch (matrixName) 
    {
        case A:
            return m_memoryBlock->matrixA.width;
        case B:
            return m_memoryBlock->matrixB.width;
        case C:
            return m_memoryBlock->matrixC.width;
    }
}
