#include "WriteProcess.h"

const std::string outputFileName = "C.txt";

WriteProcess::WriteProcess() 
{
    m_sharedMemory = new SharedMemory(WRITE);
}

WriteProcess::~WriteProcess() 
{
    delete m_sharedMemory;
}

void WriteProcess::run() 
{
    if (!m_sharedMemory->checkMemory()) 
    {
        classError(typeid(*this).name(), std::string("Unable memory"));
        return;
    }

    m_sharedMemory->setProcessStatus(WRITE, RUN);

    try 
    {
        writeMatrix();
    } 
    catch (std::runtime_error &exception) 
    {
        m_sharedMemory->crash();
        classError(typeid(*this).name(), exception.what());
    }

    m_sharedMemory->setProcessStatus(WRITE, TERMINATE);
}

void WriteProcess::writeMatrix() 
{
    auto output = [&] (std::ostream &out) -> int 
    {
        for (int y = 0; y < m_sharedMemory->getMatrixHeight(C); y++) 
        {
            while (y == m_sharedMemory->getMatrixHeight(C)) 
            {
            	
                std::cout << y << ' ' << m_sharedMemory->getMatrixHeight(C) << '\n';
                if (m_sharedMemory->isCrash()) 
                {
                    return -1;
                }
            }
            for (int x = 0; x < m_sharedMemory->getMatrixWidth(C); x++) 
            {
                out << m_sharedMemory->getValue(C, x, y) << ' ';
            }
            out << '\n';
        }
        return 0;
    };
    
        std::ofstream file(outputFileName);
        if (!file.is_open()) 
        {
            m_sharedMemory->crash();
            classError(typeid(*this).name(), std::string("Invalid filename"));
            throw std::runtime_error("Invalid filename");
        }
        output(file);
        file.close();

}
