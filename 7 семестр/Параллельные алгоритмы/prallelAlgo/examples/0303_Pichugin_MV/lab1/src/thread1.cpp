#include "matrix.h"
using namespace std;

void create_matrix(vector<vector<int>>& a,vector<vector<int>>& b, int n){
    fill_matrix(a, n);
	fill_matrix(b, n);
}

int main() {
	int n = 1000;
    auto start = chrono::high_resolution_clock::now();
	vector<vector<int>> a(n,vector<int>(n));
	vector<vector<int>> b(n, vector<int>(n));
	vector<vector<int>> c(n, vector<int>(n));
    thread create(create_matrix, ref(a),ref(b),ref(n)); // создать первый поток с созданием матриц
    create.join();  // дождаться завершения потока

    thread multiple(multi_matrix,ref(a), ref(b),ref(c),ref(n));
    multiple.join();

	thread printM(print_matrix, ref(c), ref(n));
    printM.join();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Время работы программы: "<< duration.count()<< " ms" << endl; 
	return 0;
}