#include "threads.h"
const std::string A_MATRIX_FILENAME = "A_MATRIX.txt";

const std::string B_MATRIX_FILENAME = "B_MATRIX.txt";

const std::string C_MATRIX_FILENAME = "C_MATRIX.txt";

Threads::Threads(int threads) 
{
    m_threadsNum = threads;
}

void Threads::run() 
{
    bool isCrash = false;
std::cout <<"run";
    std::thread readingThread([&] () -> void 
    {
        isCrash = !Threads::reading(&m_matrixA, &m_matrixB);
    });
    readingThread.join();


    if (!isCrash) 
    {
        std::thread calculationThread([&] () -> void 
        {
            isCrash = !Threads::calculation(&m_matrixA, &m_matrixB, &m_matrixC, m_threadsNum);
        });
        calculationThread.join();
    }

    if (!isCrash) 
    {
        std::thread writingThread([&] () -> void 
        {
            isCrash = !Threads::writing(&m_matrixC);
        });
        writingThread.join();
    }
}

bool Threads::reading(Matrix<double> *matrixA, Matrix<double> *matrixB) 
{
    matrixA->reserve(1000);
    matrixB->reserve(1000);
    
    try 
    {
    std::cout<<"READ";
        readMatrix(matrixA, A_MATRIX_FILENAME);
        
        readMatrix(matrixB, B_MATRIX_FILENAME);
        if ((*matrixA)[0].size() != matrixB->size()) 
        {
            throw std::runtime_error("Matrix A and matrix B are not compatible in size");
        }
    } 
    catch (std::runtime_error &exception) 
    {
        std::cout << exception.what() << '\n';
    }
    return true;
}

void Threads::readMatrix(Matrix<double> *matrix, std::string fileName) 
{
std::cout<<"HEY";
    std::vector<double> line;
    size_t lineWidth = 0;

    auto matrixCheck = [&] () -> bool {
        if (matrix->empty()) {
            lineWidth = line.size();
        } else {
            if (line.size() != lineWidth) {
                return false;
            }
        }
        return true;
    };

    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Reading thread error: invalid file");
    }

    double num;
    while(file >> num) {
    std::cout<<num;
        line.push_back(num);
        if (file.peek() == (int) '\n') {
            if (!matrixCheck()) {
                break;
                throw std::runtime_error("Reading thread error: input data is not a matrix");
            }
            matrix->push_back(line);
            line.clear();
        }
    }

    //matrix->push_back(line);
    /*std::cout<<(*matrix)[1].size();
    if (!matrixCheck()) {
        throw std::runtime_error("Reading thread error: input data is not a matrix");
    }*/
    file.close();

/*



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
    file.close();*/
}

bool Threads::calculation(Matrix<double> *matrixA, Matrix<double> *matrixB, Matrix<double> *matrixC, int threadsNum) 
{
    auto fragmentation = [] (int size, int amount, int index) -> std::pair<int, int> 
    {
        int start, end;
        if (index < size % amount) 
        {
            start = (size / amount + 1) * index;
            end = start + (size / amount + 1);
        } 
        else 
        {
            start = (size / amount + 1) * (size % amount) + (size / amount) * (index - size % amount);
            end = start + (size / amount);
        }
        return std::make_pair(start, end);
    };

    try {
        matrixC->resize(matrixA->size());
        int index = 0;
        std::vector<std::thread> threads(threadsNum);
        for (int i = 0; i < threadsNum; i++) 
        {
            threads[i] = std::thread([&] () -> void 
            {
                auto [start, end] = fragmentation(matrixA->size(), threadsNum, index);
                std::mutex indexMutex;
                indexMutex.lock();
                index++;
                indexMutex.unlock();
                calculateMatrix(matrixA, matrixB, matrixC, start, end);
            });
        }

        for (auto &thread : threads) 
        {
            thread.join();
        }
    } 
    catch (std::runtime_error &exception) 
    {
        std::cerr << exception.what() << '\n';
        return false;
    }
    return true;
}

void Threads::calculateMatrix(Matrix<double> *matrixA, Matrix<double> *matrixB, Matrix<double> *matrixC, int start, int end) 
{
   // throw std::runtime_error("Matrix A and matrix B are not compatible in size");
    for (int y = start; y < end; y++) 
    {
    	std::vector<double> line;
        for (int x = 0; x < (*matrixB)[0].size(); x++) 
        {
            double res = 0;
            for (int l = 0; l < (*matrixA)[0].size(); l++)
            {
            	res += (*matrixA)[y][l] * (*matrixB)[l][x];
            }
            line.push_back(res);
        }
        for (int x = 0; x < line.size(); x++) 
        {
            std::cout<<line[x]<<std::endl;
        }
        std::cout<<matrixC->size()<<std::endl;
           //throw std::runtime_error("Matrix A and matrix B are not compatible in size");
           (*matrixC)[y].resize(line.size());
        for (int x = 0; x < line.size(); x++) 
        {
            (*matrixC)[y][x] = line[x];
        }
           // throw std::runtime_error("Matrix A and matrix B are not compatible in size");
    }
/*
    std::vector<double> line;
    for (int y = start; y < end; y++) 
    {
        for (int x = 0; x < (*matrixA)[0].size(); x++) 
        {
            line.push_back((*matrixA)[y][x] + (*matrixB)[y][x]);
        }
        (*matrixC)[y].resize(line.size());
        for (int x = 0; x < line.size(); x++) 
        {
            (*matrixC)[y][x] = line[x];
        }
        line.clear();
    }*/
        //throw std::runtime_error("Matrix A and matrix B are not compatible in size");
}

bool Threads::writing(Matrix<double> *matrixC) 
{
    try 
    {
        writeMatrix(matrixC);
    } 
    catch (std::runtime_error &exception) 
    {
        std::cerr << exception.what() << '\n';
        return false;
    }
    return true;
}

void Threads::writeMatrix(Matrix<double> *matrix) 
{
    auto output = [&] (std::ostream &out) -> void 
    {
        for (int y = 0; y < matrix->size(); y++) 
        {
            for (int x = 0; x < (*matrix)[y].size(); x++) 
            {
                out << (*matrix)[y][x] << ' ';
            }
            out << '\n';
        }
    };

    std::ofstream file(C_MATRIX_FILENAME);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Writing thread error: invalid file");
    }
    output(file);
    file.close();
}
