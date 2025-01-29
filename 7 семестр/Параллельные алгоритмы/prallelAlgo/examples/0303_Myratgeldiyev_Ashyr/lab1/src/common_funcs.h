#include<iostream>
#include<fstream>
#include<vector>

#define PAIR_INT const pair<int, int>
#define MATRIX vector<vector<int>>

using namespace std;

void writeMatrix(ofstream &out, PAIR_INT& dim);

void generateTxtFile(const char* filename, PAIR_INT& dim1, PAIR_INT& dim2);

void readMatrixFromFile(ifstream& in, MATRIX& matrix);

void readMatricesFromFile(const char* filename, MATRIX& m1, MATRIX& m2);

void printMatrixToFile(const char* filename, const MATRIX& matrix);