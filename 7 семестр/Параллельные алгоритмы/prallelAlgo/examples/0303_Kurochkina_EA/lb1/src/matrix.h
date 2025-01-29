#include<iostream>
#include<fstream>
#include<vector>

#define PAIR const pair<int, int>
#define MATRIX vector<vector<int>>

using namespace std;

void generateMatrixToFile(ofstream &file, PAIR& dim);

void generateMatricesToFile(const char* filePath, PAIR& dim1, PAIR& dim2);

void readMatrixFromFile(ifstream& file, MATRIX& matrix);

void readMatricesFromFile(const char* filePath, MATRIX& m1, MATRIX& m2);

void writeMatrixToFile(const char* filePath, const MATRIX& matrix);