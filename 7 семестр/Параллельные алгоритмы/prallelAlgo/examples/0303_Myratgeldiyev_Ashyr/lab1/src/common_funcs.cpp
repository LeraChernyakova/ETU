#include "./common_funcs.h"

void writeMatrix(ofstream &out, PAIR_INT& dim) {
	out << dim.first << ' ' << dim.second << '\n';
	for (int i = 0; i < dim.first; i++) {
		for (int j = 0; j < dim.second; j++) {
			out << (rand() % 200) - 100;
			if (j + 1 < dim.second) out << ' ';
		}
		out << '\n';
	}
}

void generateTxtFile(const char* filename, PAIR_INT& dim1, PAIR_INT& dim2) {
	ofstream out;
	out.open(filename);
	if (!out.is_open()) {
		out.close();
		cout << "Error during opening the file.\n";
		exit(1);
		return;
	}
	writeMatrix(out, dim1);
	writeMatrix(out, dim2);
	out.close();
}

void readMatrixFromFile(ifstream& in, MATRIX& matrix) {
	int rows, cols, tmp;
	in >> rows >> cols;
	// cout << rows << ' ' << cols << '\n';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			in >> tmp;
			matrix[i][j] = tmp;
			// cout << tmp << ' ';
		}
		// cout << '\n';
	}
}

void readMatricesFromFile(const char* filename, MATRIX& m1, MATRIX& m2) {
	ifstream in(filename);
	readMatrixFromFile(in, m1);
	readMatrixFromFile(in, m2);
	in.close();
}

void printMatrixToFile(const char* filename, const MATRIX& matrix) {
	int rows = matrix.size(), cols = matrix[0].size();
	ofstream out;
	out.open(filename);
	if (!out.is_open()) {
		out.close();
		cout << "Error during opening the file " << filename << ".\n";
		exit(1);
		return;
	}
	out << rows << ' ' << cols << '\n';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			out << matrix[i][j];
			if (j + 1 < cols) out << ' ';
		}
		out << '\n';
	}
	out.close();
}