#include "CalculateProcess.h"

CalculateProcess::CalculateProcess() 
{
    m_sharedMemory = new SharedMemory(CALCULATE);
}

CalculateProcess::~CalculateProcess() 
{
    delete m_sharedMemory;
}

void CalculateProcess::run() 
{
    if (!m_sharedMemory->checkMemory()) 
    {
    	classError(typeid(*this).name(), std::string("Unable memory"));
        return;
    }

    m_sharedMemory->setProcessStatus(CALCULATE, RUN);

    try 
    {
        calculateMatrix();
    } 
    catch (std::runtime_error &exception) 
    {
        m_sharedMemory->crash();
        classError(typeid(*this).name(), exception.what());
    }
    m_sharedMemory->setProcessStatus(CALCULATE, TERMINATE);
}

void CalculateProcess::calculateMatrix()
{
    while (m_sharedMemory->getProcessStatus(READ) < RUN) 
    {
        if (m_sharedMemory->isCrash()) 
        {
            return;
        }
    }

    while (m_sharedMemory->getMatrixHeight(B) == 0) 
    {
        if (m_sharedMemory->isCrash()) 
        {
            return;
        }
    }

    for (int y = 0; y < m_sharedMemory->getMatrixHeight(A); y++) 
    {
        while (y == m_sharedMemory->getMatrixHeight(B)) 
        {
            if (m_sharedMemory->isCrash()) 
            {
                return;
            }
        }
        for (int x = 0; x < m_sharedMemory->getMatrixWidth(B); x++) 
        {
            double res = 0;
            for (int l = 0; l < m_sharedMemory->getMatrixWidth(A); l++)
            {
            	res += m_sharedMemory->getValue(A, l, y) * m_sharedMemory->getValue(B, x, l);
            }
            m_sharedMemory->setValue(res, C, x, y);
        }
    }
}
