#include "pthreads.h"
#include <chrono>

#define CURRENT_TIME chrono::steady_clock::now()

using namespace std;

unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::milliseconds>(second - first).count();
}

int main() {
    std::cout << "====Сравнение алгоритмов параллельного умножения====\n";
    int dim = 0, thread_amount = 0;
    std::cout<<"Введите размерность матрицы ";
    std::cin>>dim;
    std::cout<<"Введите количество потоков ";
    std::cin>>thread_amount;
    chrono::time_point<std::chrono::steady_clock> start;
    Matrix res1, res2;

    Matrix a(dim, dim, true), b(dim, dim, true);
    
    start = CURRENT_TIME;
    res1 = strassen_alg(a, b);
    cout << "\nАлгоритм Штрассена: " << get_time_diff(start, CURRENT_TIME) << "ms\n";
    //cout << cur_res;
    
    start = CURRENT_TIME;
    res2 = parallel(a, b, thread_amount);
    cout << "Многопоточное умножение: " << get_time_diff(start, CURRENT_TIME) << "ms\n";
    //cout << res2;

    cout<<(res1 == res2);

    return 0;
}