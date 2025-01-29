#include "task1.h"
#define ROWS1 3
#define COLS1 2
#define ROWS2 2
#define COLS2 1
#define MOD 200
#define FILENAME "matrices.txt"
#define OUTPUT_FILE "result1.txt"

using namespace std;

int MY_KEY = 1;

int main() {
	int* shared_mem = (int*)createSharedMem();
	generateTxtFile(FILENAME, make_pair(ROWS1, COLS1), make_pair(ROWS2, COLS2));
	runProcess(matrixPrepare, shared_mem);
	runProcess(matrixCalculate, shared_mem);
	runProcess(matrixPrintToFile, shared_mem);
	// runProcess(matrixPrint, shared_mem);
	clearSharedMem();
	return 0;
}

void runProcess(const function<void(int*)> &func, int* ptr) {
	pid_t pid;
	int status;
	switch(pid=fork()) {
		case -1: {
			cerr << "Error while forking.\n";
			exit(1);
		}
		case 0: {
			func(ptr);
			cout << "executed " << getpid() << '\n';
			exit(0);
		}
		default:
			cout << getpid() << " waiting for " << pid << endl;
			wait(&status);

	}	
}

void* createSharedMem() {
	const int size = ((ROWS1 * COLS1) + (ROWS2 * COLS2) + 4) * sizeof(int);
	auto id = shmget(MY_KEY, size, 0644 | IPC_CREAT);
	auto pointer = shmat(id, nullptr, 0);
	return pointer;
}

void clearSharedMem() {
	const int size = ((ROWS1 * COLS1) + (ROWS2 * COLS2) + 4) * sizeof(int);
	shmid_ds tmp;
	auto id = shmget(MY_KEY, size, 0644 | IPC_EXCL);
	auto pointer = shmat(id, nullptr, 0);
	shmctl(id, 0x00000000, nullptr);
	// cout << "cleaned\n";
}

int writeToPointerFromFile(ifstream& in, int* ptr, int ptrOffset) {
	int rows, cols, tmp;
	in >> rows >> cols;
	ptr[ptrOffset] = rows; ptr[ptrOffset + 1] = cols;
	cout << rows << ' ' << cols << '\n';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			in >> tmp;
			ptr[ptrOffset + (i*cols + j + 2)] = tmp;
			cout << tmp << ' ';
		}
		cout << '\n';
	}
	return 2 + rows * cols;
}

void matrixPrepare(int* ptr) {
	ifstream in(FILENAME);
	int offset = writeToPointerFromFile(in, ptr, 0);
	writeToPointerFromFile(in, ptr, offset);
	in.close();
}

int multiplyRowCol(int* ptr, PAIR_INT& dim1, PAIR_INT& dim2, PAIR_INT& cur) {
	int res = 0;
	int offset = dim1.first * dim1.second + 2 + 2;
	for (int i = 0; i < dim1.second; i++) {
		res += (ptr[2 + cur.first*dim1.second + i] * ptr[offset + i*dim2.second + cur.second]);
	}
	return res;
}

void matrixCalculate(int* ptr) {
	PAIR_INT dim1 = make_pair(ptr[0], ptr[1]), 
				   dim2 = make_pair(ptr[dim1.first * dim1.second + 2], ptr[dim1.first * dim1.second + 3]);
	if (dim1.second != dim2.first) {
		cout << "Can't multiply matrices of these dimensions.\n";
		clearSharedMem();
		exit(1);
		return;
	}

	MATRIX matrix(dim1.first, vector<int>(dim2.second));
	for (int i = 0; i < dim1.first; i++) {
		for (int j = 0; j < dim2.second; j++) {
			matrix[i][j] = multiplyRowCol(ptr, dim1, dim2, make_pair(i, j));
		}
	}
	ptr[0] = dim1.first;
	ptr[1] = dim2.second;
	for (int i = 0; i < ptr[0]; i++) {
		for(int j = 0; j < ptr[1]; j++) {
			ptr[2 + ptr[1]*i + j] = matrix[i][j];
		}
	}

}

void matrixPrint(int* ptr) {
	int rows = ptr[0], cols = ptr[1];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << ptr[(i*cols + j + 2)] << ' ';
		}
		cout << '\n';
	}
}

void matrixPrintToFile(int* ptr) {
	ofstream out;
	out.open(OUTPUT_FILE);
	if (!out.is_open()) {
		out.close();
		cout << "Error during opening the file " << OUTPUT_FILE << ".\n";
		exit(1);
		return;
	}
	out << ptr[0] << ' ' << ptr[1] << '\n';
	for (int i = 0; i < ptr[0]; i++) {
		for (int j = 0; j < ptr[1]; j++) {
			out << ptr[2 + i*ptr[1] + j];
			if (j + 1 < ptr[1]) out << ' ';
		}
		out << '\n';
	}
	out.close();
}

