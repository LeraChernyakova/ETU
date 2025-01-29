#include "threads.h"
const std::string A_MATRIX_FILENAME = "A_MATRIX.txt";
const std::string B_MATRIX_FILENAME = "B_MATRIX.txt";
const std::string C_MATRIX_FILENAME = "C_MATRIX.txt";

Threads::Threads() 
{
    m_readingStatus = START;
    m_calculatingStatus = START;
    m_writingStatus = START;
    m_isCrash = false;
}

void Threads::run() 
{
    std::thread readThread(Threads::reading,
                           &m_matrixA,
                           &m_matrixB,
                           &m_readingStatus,
                           &m_isCrash);
    readThread.join();

    std::thread calculateThread(Threads::calculation,
                                &m_matrixA,
                                &m_matrixB,
                                &m_matrixC,
                                &m_readingStatus,
                                &m_calculatingStatus,
                                &m_isCrash);
    calculateThread.join();

    std::thread writeThread(Threads::writing,
                            &m_matrixC,
                            &m_calculatingStatus,
                            &m_writingStatus,
                            &m_isCrash);
    writeThread.join();
}

void Threads::reading(Matrix<double> *matrixA,
                      Matrix<double> *matrixB,
                      status *readingStatus,
                      bool *isCrash)
{
    *readingStatus = RUN;

    try 
    {
        readMatrix(matrixA, A_MATRIX_FILENAME);
        readMatrix(matrixB, B_MATRIX_FILENAME);
	/*for (int i= 0; i < matrixB->size(); i++)
	{
	for (int j=0; j < (*matrixB)[0].size(); j++)
	{
	std::cout<<(*matrixB)[i][j]<<matrixB->size() <<j<<std::endl;
	
	}
	}
	//std::cout << (int) matrixB->size();
	std::cout << (*matrixA)[0].size();*/
        if ((*matrixA)[0].size() != matrixB->size()) 
        {
            throw std::runtime_error("Matrix A and matrix B are not compatible in size");
        }
    } 
    catch (std::runtime_error &exception) 
    {
        *isCrash = true;
        std::cout << exception.what() << '\n';
    }

    *readingStatus = TERMINATE;
}

void Threads::readMatrix(Matrix<double> *matrix, std::string fileName) 
{
    std::vector<double> line;
    size_t lineWidth = 0;

    auto matrixCheck = [&] () -> bool 
    {
        if (matrix->empty()) 
        {
            lineWidth = line.size();
        } 
        else 
        {
            if (line.size() != lineWidth) 
            {
                return false;
            }
        }
        return true;
    };

    std::ifstream file(fileName);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Invalid file");
    }

    double num;
    while(file >> num) 
    {
        line.push_back(num);
        std::cout <<num ;
        if (file.peek() == (int) '\n') 
        {
            if (!matrixCheck()) 
            {
                break;
            }
            matrix->push_back(line);
            line.clear();
        }
    }
    file.close();
}

void Threads::calculation(Matrix<double> *matrixA, Matrix<double> *matrixB, Matrix<double> *matrixC, status *readingStatus, status *calculationStatus, bool *isCrash) 
{
    *calculationStatus = RUN;

    try 
    {
        while (*readingStatus < RUN) 
        {
            if (*isCrash) 
            {
                return;
            }
        }
        calculateMatrix(matrixA, matrixB, matrixC, isCrash);
    } 
    catch (std::runtime_error &exception) 
    {
        *isCrash = true;
        std::cerr << exception.what() << '\n';
    }

    *calculationStatus = TERMINATE;
}

void Threads::calculateMatrix(Matrix<double> *matrixA, Matrix<double> *matrixB, Matrix<double> *matrixC, bool *isCrash) 
{

    while (matrixB->empty()) 
    {
        if (*isCrash) 
        {
            return;
        }
    }
    
    for (int y = 0; y < matrixA->size(); y++) 
    {
    	std::vector<double> line;
        while (y == matrixB->size()) 
        {
            if (*isCrash) 
            {
                return;
            }
        }
        for (int x = 0; x < (*matrixB)[0].size(); x++) 
        {
            double res = 0;
            for (int l = 0; l < (*matrixA)[0].size(); l++)
            {
            	res += (*matrixA)[y][l] * (*matrixB)[l][x];
            }
            line.push_back(res);
        }
        matrixC->push_back(line);
    }
}

void Threads::writing(Matrix<double> *matrixC, status *calculationStatus, status *writingStatus, bool *isCrash) 
{
    *writingStatus = RUN;

    try 
    {
        writeMatrix(matrixC, calculationStatus, isCrash);
    } 
    catch (std::runtime_error &exception) 
    {
        *isCrash = true;
        std::cerr << exception.what() << '\n';
    }

    *writingStatus = TERMINATE;
}

void Threads::writeMatrix(Matrix<double> *matrix, status *calculationStatus, bool *isCrash) 
{
    auto output = [&] (std::ostream &out) -> void 
    {
        for (int y = 0; *calculationStatus != TERMINATE || matrix->size() > y; y++) 
        {
            while (y == matrix->size()) 
            {
                if (*isCrash) 
                {
                    return;
                }
            }
            for (int x = 0; x < (*matrix)[0].size(); x++) 
            {
                out << (*matrix)[y][x] << ' ';
            }
            out << '\n';
        }
    };

    std::ofstream file(C_MATRIX_FILENAME);
    if (!file.is_open()) 
    {
        *isCrash = true;
        throw std::runtime_error("Writing thread error: invalid file");
    }
    output(file);
    file.close();
}
