#include <fstream>
#include "matrix.h"
#include "string"
#include <thread>
using namespace std;
int StartSizeMatrix;

const std::string OUTPUT = "C.txt";

void matricesGenerate(Matrix& A, Matrix& B, Matrix& C, int N) 
{
    A = Matrix(N, N);
    B = Matrix(N, N);
    C = Matrix(N, N);
}

void strassenMultiple(Matrix initA, Matrix initB, Matrix& C, int limit)
{
    int N = initA.matrix.size();
    if(N > 2 && N > limit)
    {
    	int half = N / 2;
        Matrix A11 = Matrix(half, half);
        Matrix A12 = Matrix(half, half);
        Matrix A21 = Matrix(half, half);
        Matrix A22 = Matrix(half, half);
        Matrix B11 = Matrix(half, half);
        Matrix B12 = Matrix(half, half);
        Matrix B21 = Matrix(half, half);
        Matrix B22 = Matrix(half, half);
        for (int i = 0; i < half; i++) 
        {
            for (int j = 0; j < half; j++) 
            {
                A11.matrix[i][j] = initA.matrix[i][j];
                A12.matrix[i][j] = initA.matrix[i][j + half];
                A21.matrix[i][j] = initA.matrix[i + half][j];
                A22.matrix[i][j] = initA.matrix[i + half][j + half];
                B11.matrix[i][j] = initB.matrix[i][j];
                B12.matrix[i][j] = initB.matrix[i][j + half];
                B21.matrix[i][j] = initB.matrix[i + half][j];
                B22.matrix[i][j] = initB.matrix[i + half][j + half];
            }
        }
        Matrix P1(half,half); 
        Matrix P2(half,half); 
        Matrix P3(half,half); 
        Matrix P4(half,half); 
        Matrix P5(half,half); 
        Matrix P6(half,half); 
        Matrix P7(half,half);
    if(N == StartSizeMatrix)
    {
        std::thread p1_thread(strassenMultiple, A11 + A22, B11 + B22, std::ref(P1),limit);
        std::thread p2_thread(strassenMultiple, A21 + A22, B11, std::ref(P2),limit);
        std::thread p3_thread(strassenMultiple, A11, B12 - B22, std::ref(P3),limit);
        std::thread p4_thread(strassenMultiple, A22, B21 - B11, std::ref(P4),limit);
        std::thread p5_thread(strassenMultiple, A11 + A12, B22, std::ref(P5),limit);
        std::thread p6_thread(strassenMultiple, A21 - A11, B11 + B12, std::ref(P6),limit);
        std::thread p7_thread(strassenMultiple, A12 - A22, B21 + B22, std::ref(P7),limit); 
        p1_thread.join();
        p2_thread.join();
        p3_thread.join();
        p4_thread.join();
        p5_thread.join();
        p6_thread.join();
        p7_thread.join();
    }
    else
    {
        strassenMultiple(A11 + A22, B11 + B22,P1,limit);
        strassenMultiple(A21 + A22, B11,P2,limit);
        strassenMultiple(A11,B12 - B22,P3,limit);
        strassenMultiple(A22, B21 - B11,P4,limit);
        strassenMultiple(A11 + A12, B22,P5,limit);
        strassenMultiple( A21 - A11, B11 + B12,P6,limit);
        strassenMultiple(A12 - A22, B21 + B22,P7,limit);
    }
    // вычисляем блоки
    Matrix C11 = P1 + P4;
    C11 = C11 - P5;
    C11 = C11 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1;
    C22 = C22 - P2;
    C22 = C22 + P3;
    C22 = C22 + P6;
    // Собираем матрицу
    for (int i = 0; i < half; i++) 
    {
        for (int j = 0; j < half; j++) 
        {
            C.matrix[i][j] = C11.matrix[i][j];
            C.matrix[i][j + half] = C12.matrix[i][j];
            C.matrix[i + half][j] = C21.matrix[i][j];
            C.matrix[i + half][j + half] = C22.matrix[i][j];
        }
    }
    }
    else
    {
        initA.multiple(initB, C);
    }
}

void multiple(Matrix& A, Matrix& B, Matrix& C, int shiftRow, int threadCount){ 
    if(threadCount == 1)
    {
        A.multiple(B, C);
    }
    else
    {
        A.multiple(B, C, shiftRow, threadCount);
    }
}

void multipleExtended(Matrix& A, Matrix& B,Matrix& C,int startRow,int endRow){ 

    A.multipleExtend(B,C,startRow,endRow);
}

void outPut(Matrix& C)
{ // вывод результата в файл
    C.fileOutput(OUTPUT);
}

int main()
{
    int choice = 3;
    int N = 16;
    int threadsCount = 7;
    Matrix A;
    Matrix B;
    Matrix cur;
    Matrix C;
    
    switch(choice)
    {
        case 0:
        {
            matricesGenerate(A, B, C, N);
            std::vector<std::thread> multipleThreads = std::vector<std::thread>(threadsCount); 
            for (int index = 0; index < threadsCount; index++) 
            {
                multipleThreads[index] = std::thread(multiple,
                                        std::ref(A), 
                                        std::ref(B),
                                        std::ref(C),
                                        index,
                                        threadsCount);
            }
            for(auto& thread: multipleThreads) 
            {
                thread.join(); 
            }
            outPut(C);
            break;
	    }
        case 1:
        {
            matricesGenerate(A, cur, C, N);
            B = Matrix(N,N);
            B.transp(cur);
            
            std::vector<std::thread> multipleThreads = std::vector<std::thread>(threadsCount); 
            for (int index = 0; index < threadsCount; index++)
            {    
                int startRow = index * (N / threadsCount);
                int endRow = (index == threadsCount - 1) ? N : (index + 1) * (N / threadsCount); // потоку start - end + 1 строк
                multipleThreads[index] = std::thread(multipleExtended,
                                        std::ref(A), 
                                        std::ref(B),
                                        std::ref(C),
                                        startRow,
                                        endRow);
            }
            for(auto& thread: multipleThreads) 
            {
                thread.join(); 
            }
            outPut(C);
            break;
		}
        case 2:
        {
            int count = 8;
            StartSizeMatrix = N;
            matricesGenerate(A, B, C, N);
            strassenMultiple(A, B, C, N/count);
            outPut(C);
            break;
		}
        case 3:
	    {
	        Matrix A;
            Matrix B;
            //Matrix cur1;
            Matrix C1;
            matricesGenerate(A, B, C1, N);

            std::vector<std::thread> multipleThreads = std::vector<std::thread>(threadsCount); 
            for (int index = 0; index < threadsCount; index++) 
            {
                multipleThreads[index] = std::thread(multiple,
                                        std::ref(A), 
                                        std::ref(B),
                                        std::ref(C1),
                                        index,
                                        threadsCount);
            }
            for(auto& thread: multipleThreads) 
            {
                thread.join(); 
            }
            Matrix C2 = Matrix(N, N);
            int count = 8;
            StartSizeMatrix = N;
            strassenMultiple(A, B, C2, N/count);
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    if (C1.matrix[i][j] != C2.matrix[i][j])
                    {
                        std::cout<<"Не работает что-то";
                        exit(1);
                    }
                }
            }
            
            break;
		}
       }
   
   return 0;
}

