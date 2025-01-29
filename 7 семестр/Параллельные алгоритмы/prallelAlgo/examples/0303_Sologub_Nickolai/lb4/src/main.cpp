#include <iostream>
#include "matrix.h"
#include <thread>
using namespace std;
int StartSizeMatrix;
void Create(Matrix& first, Matrix& second,Matrix& result,int N) // создание матриц
{
    first =  Matrix(N,N);
    second = Matrix(N,N);
    result = Matrix(N,N);

}
void StrassenMultiple(Matrix first, Matrix second, Matrix &result, int BigSize){
    
    int N = first.matrix.size();
    if(N > 2 && N > BigSize){
    int half = N / 2;
        // Разбиваем матрицы на четыре подматрицы
        Matrix A11 = Matrix(half,half);
        Matrix A12 = Matrix(half,half);
        Matrix A21 = Matrix(half,half);
        Matrix A22 = Matrix(half,half);
        Matrix B11 = Matrix(half,half);
        Matrix B12 = Matrix(half,half);
        Matrix B21 = Matrix(half,half);
        Matrix B22 = Matrix(half,half);
        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                A11.matrix[i][j] = first.matrix[i][j];
                A12.matrix[i][j] = first.matrix[i][j + half];
                A21.matrix[i][j] = first.matrix[i + half][j];
                A22.matrix[i][j] = first.matrix[i + half][j + half];
                B11.matrix[i][j] = second.matrix[i][j];
                B12.matrix[i][j] = second.matrix[i][j + half];
                B21.matrix[i][j] = second.matrix[i + half][j];
                B22.matrix[i][j] = second.matrix[i + half][j + half];
            }
        }
        Matrix P1(half,half); 
        Matrix P2(half,half); 
        Matrix P3(half,half); 
        Matrix P4(half,half); 
        Matrix P5(half,half); 
        Matrix P6(half,half); 
        Matrix P7(half,half);
    if(N == StartSizeMatrix){
        std::thread p1_thread(StrassenMultiple, A11 + A22, B11 + B22, std::ref(P1),BigSize);
        std::thread p2_thread(StrassenMultiple, A21 + A22, B11, std::ref(P2),BigSize);
        std::thread p3_thread(StrassenMultiple, A11, B12 - B22, std::ref(P3),BigSize);
        std::thread p4_thread(StrassenMultiple, A22, B21 - B11, std::ref(P4),BigSize);
        std::thread p5_thread(StrassenMultiple, A11 + A12, B22, std::ref(P5),BigSize);
        std::thread p6_thread(StrassenMultiple, A21 - A11, B11 + B12, std::ref(P6),BigSize);
        std::thread p7_thread(StrassenMultiple, A12 - A22, B21 + B22, std::ref(P7),BigSize); 
        p1_thread.join();
        p2_thread.join();
        p3_thread.join();
        p4_thread.join();
        p5_thread.join();
        p6_thread.join();
        p7_thread.join();
    }
    else{
        StrassenMultiple(A11 + A22, B11 + B22,P1,BigSize);
        StrassenMultiple(A21 + A22, B11,P2,BigSize);
        StrassenMultiple(A11,B12 - B22,P3,BigSize);
        StrassenMultiple(A22, B21 - B11,P4,BigSize);
        StrassenMultiple(A11 + A12, B22,P5,BigSize);
        StrassenMultiple( A21 - A11, B11 + B12,P6,BigSize);
        StrassenMultiple(A12 - A22, B21 + B22,P7,BigSize);
    }
    // вычисляем блоки матрицы результата
        Matrix C11 = P1 + P4;
        C11 = C11 - P5;
        C11 = C11 + P7;
        Matrix C12 = P3 + P5;
        Matrix C21 = P2 + P4;
        Matrix C22 = P1;
        C22 = C22 - P2;
        C22 = C22 + P3;
        C22 = C22 + P6;
    // Собираем результат в одну матрицу
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            result.matrix[i][j] = C11.matrix[i][j];
            result.matrix[i][j + half] = C12.matrix[i][j];
            result.matrix[i + half][j] = C21.matrix[i][j];
            result.matrix[i + half][j + half] = C22.matrix[i][j];
        }
    }
    }
    else{
        first.multiple(second,result);
    }
}

void MultipleSimple(Matrix& first, Matrix& second,Matrix& result,int shiftRow,int threadCount){ // умножение матриц
    if(threadCount == 1){
        first.multiple(second,result);
    }
    else{
        first.multiple(second,result,shiftRow,threadCount);
    }
}


void MultipleExtended(Matrix& first, Matrix& second,Matrix& result,int startRow,int endRow){ // умножение матриц

    first.multipleExtend(second,result,startRow,endRow);
}
void outPut(Matrix& result){ // вывод результата в файл
    result.fileOutput("resultThreads.txt");
}


int main(){
    int choice = 0;
    int N = 10;
    int threadsCount = 1;
    cout << "Введите:\n0 для параллельного умножения\n1 для масштабируемого разбиения\n2 для умножения штрассена\n3 для выхода\n";
    cin >> choice;
    Matrix first;
    Matrix second;
    Matrix cur;
    Matrix result;
    
    switch(choice){
        case 0:{
            cout << "Введите размерность матриц:\n";
            cin >> N;
            cout << "Введите количество потоков:\n";
            cin >> threadsCount;
            Create(first,second,result,N);
            auto startTime = std::chrono::steady_clock::now(); // засечь время начала
           // cout << first;
           // cout << second;
            std::vector<std::thread> multipleThreads = std::vector<std::thread>(threadsCount); // вектор из P потоков
                for (int index = 0; index < threadsCount; index++) {
                    multipleThreads[index] = std::thread(MultipleSimple,std::ref(first), std::ref(second),std::ref(result),index,threadsCount); // создать потоки для умножения
                }
                for(auto& thread: multipleThreads) {
                     thread.join(); // дождаться завершения
                }
                std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
                std::cout << "Время работы: " << endTime.count() << " секунд" << std::endl;
               // cout << result;
                outPut(result);
                break;
	        }
        case 1:{
                cout << "Введите размерность матриц:\n";
                cin >> N;
                cout << "Введите количество потоков:\n";
                cin >> threadsCount;
                Create(first,cur,result,N);
                second = Matrix(N,N);
                second.transp(cur);
                
                auto startTime = std::chrono::steady_clock::now(); // засечь время начала
               // cout << first;
               // cout << cur;
                std::vector<std::thread> multipleThreads = std::vector<std::thread>(threadsCount); // вектор из P потоков
                for (int index = 0; index < threadsCount; index++) {
                    int startRow = index * (N / threadsCount);
                    int endRow = (index == threadsCount - 1) ? N : (index + 1) * (N / threadsCount); // выделить каждому потоку start - end + 1 строк
                    multipleThreads[index] = std::thread(MultipleExtended,std::ref(first), std::ref(second),std::ref(result),startRow,endRow); // создать потоки для умножения
                }
                for(auto& thread: multipleThreads) {
                     thread.join(); // дождаться завершения
                }
                std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
                std::cout << "Время работы: " << endTime.count() << " секунд" << std::endl;
               // cout << result;
                outPut(result);
                break;
		    }
        case 2:{
            cout << "Введите размерность матриц:\n";
            cin >> N;
            int count = 8;
            int freeThreads = 16;
            StartSizeMatrix = N;
            Create(first,second,result,N);
            auto startTime = std::chrono::steady_clock::now(); // засечь время начала
          //  cout << first;
           // cout << second;
            StrassenMultiple(first,second,result,N/count);
            std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
            std::cout << "Время работы: " << endTime.count() << " секунд" << std::endl;
           // cout << result;
            outPut(result);
            break;
		}
        case 3:
		{
            break;
		}
       }
    
   return 0;
}
