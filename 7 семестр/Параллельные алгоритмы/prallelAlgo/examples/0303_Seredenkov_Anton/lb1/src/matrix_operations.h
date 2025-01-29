#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void generate_matrix(vector<vector<int>>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //matrix[i][j] = rand() % 10000 - 5000;
            matrix[i][j] = rand() % 19 - 9;
            cout<< matrix[i][j] << " ";
        }
        cout<<endl;
    }
    cout<< "======"<< endl;
}


vector<vector<int>> multiply_matrices(vector<vector<int>>& a, vector<vector<int>>& b, int m, int n) {
    vector<vector<int>> c(m, vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

void print_res(vector<vector<int>>& result_matrix, int m){
    ofstream result;
    result.open("matrix_result.txt");
    //cout << "The product of the two matrices is:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            //cout << result_matrix[i][j] << " ";
            result << result_matrix[i][j] << " ";
        }
        //cout << endl;
        result << endl;
    }
}