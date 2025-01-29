#include "./matrix.h"

void generateMatrixToFile(ofstream &file, PAIR& dim) {
	file << dim.first << ' ' << dim.second << '\n';
	for (int i = 0; i < dim.first; i++) {
		for (int j = 0; j < dim.second; j++) {
      file << rand() % 100;
			if (j + 1 < dim.second) file << ' ';
		}
		file << '\n';
	}
}

void generateMatricesToFile(const char* filePath, PAIR& dim1, PAIR& dim2) {
	ofstream file;
	file.open(filePath);
	if (!file.is_open()) {
		file.close();
		cout << "Ошибка открытия файла\n";
		exit(1);
		return;
	}
	generateMatrixToFile(file, dim1);
	generateMatrixToFile(file, dim2);
	file.close();
}

void readMatrixFromFile(ifstream& file, MATRIX& matrix) {
	int rows, cols, tmp;
	file >> rows >> cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file >> tmp;
			matrix[i][j] = tmp;
		}
	}
}

void readMatricesFromFile(const char* filePath, MATRIX& m1, MATRIX& m2) {
	ifstream file(filePath);
	readMatrixFromFile(file, m1);
	readMatrixFromFile(file, m2);
	file.close();
}

void writeMatrixToFile(const char* filePath, const MATRIX& matrix) {
	int rows = matrix.size(), cols = matrix[0].size();
	ofstream file;
	file.open(filePath);
	if (!file.is_open()) {
		file.close();
		cout << "Ошибка открытия файла\n";
		exit(1);
		return;
	}
	file << rows << ' ' << cols << '\n';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file << matrix[i][j];
			if (j + 1 < cols) file << ' ';
		}
		file << '\n';
	}
	file.close();
}