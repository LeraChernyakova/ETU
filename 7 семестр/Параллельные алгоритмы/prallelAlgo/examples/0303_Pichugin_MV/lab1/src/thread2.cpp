#include "matrix.h"
using namespace std;

void create_matrix(vector<vector<int>>& a,vector<vector<int>>& b, int n){
    fill_matrix(a, n);
	fill_matrix(b, n);
}

void multiply(int start, int end, const vector<vector<int>>& a, const vector<vector<int>>& b, vector<vector<int>>& c,int n) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
	int n = 1000;
    int th = 32;
    auto start = chrono::high_resolution_clock::now();
	vector<vector<int>> a(n,vector<int>(n));
	vector<vector<int>> b(n, vector<int>(n));
	vector<vector<int>> c(n, vector<int>(n));
    thread create(create_matrix, ref(a),ref(b),ref(n)); // создать первый поток с созданием матриц
    create.join();  // дождаться завершения потока

    vector<thread> threads;
    int chunk_size = n / th;
    for (int i = 0; i < th; i++) {
        int start = i * chunk_size;
        int end = (i == th - 1) ? n : (i + 1) * chunk_size;
        threads.emplace_back(multiply, start, end, ref(a), ref(b), ref(c), ref(n));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    print_matrix(c, n);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Время работы программы: "<< duration.count()<< " ms" << endl;
    return 0;
}