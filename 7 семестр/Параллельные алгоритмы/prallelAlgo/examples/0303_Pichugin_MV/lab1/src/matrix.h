#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
using namespace std;

void fill_matrix(vector<vector<int>>& matr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matr[i][j] = rand() % 10;
		}
	}
}
void write_matrix(int* matr, int n) {
	ofstream result;
	int index = 0;
	result.open("result.txt");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result << matr[index] << " ";
			index++;
		}
		result << endl;
	}
}

void print_matrix(vector<vector<int>>& matr, int n){
    ofstream result;
    result.open("result.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result << matr[i][j] << " ";
        }
        result << endl;
    }
}

void multi_matrix(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j]=0;
			for (int k = 0; k < n; k++) {
				c[i][j]+= a[i][k] * b[k][j];
			}
		}
	}
}

int * matrix_to_array(vector<vector<int>>& a,int n){
    int *buf = new int[n*n];
    int index = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            buf[index] = a[i][j]; // записываем представление матрицы в массив int для записи и чтения дескриптора
            index++;
            }
        }
    return buf;
}