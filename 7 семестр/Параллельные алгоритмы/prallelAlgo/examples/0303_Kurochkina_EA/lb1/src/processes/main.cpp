#include "../matrix.h"
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <functional>
#include<unistd.h>
#include<utility>
#include<future>
#include<vector>

using namespace std;
#define ROWS1 3
#define COLS1 2
#define ROWS2 2
#define COLS2 1
#define FILE_MATRICES "processes/matrices.txt"
#define RESULT "processes/result.txt"


int MY_KEY = 1;

void* createMem() {
	const int size = ((ROWS1 * COLS1) + (ROWS2 * COLS2) + 4) * sizeof(int);
	auto id = shmget(MY_KEY, size, 0644 | IPC_CREAT);
	auto pointer = shmat(id, nullptr, 0);
	return pointer;
}

void clearMem() {
	const int size = ((ROWS1 * COLS1) + (ROWS2 * COLS2) + 4) * sizeof(int);
	shmid_ds cur;
	auto id = shmget(MY_KEY, size, 0644 | IPC_EXCL);
	auto pointer = shmat(id, nullptr, 0);
	shmctl(id, 0x00000000, nullptr);
}

int getFromFile(ifstream& file, int* ptr, int ptrOffset) {
	int rows, cols, cur;
	file >> rows >> cols;
	ptr[ptrOffset] = rows; ptr[ptrOffset + 1] = cols;
	cout << rows << ' ' << cols << '\n';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file >> cur;
			ptr[ptrOffset + (i*cols + j + 2)] = cur;
			cout << cur << ' ';
		}
		cout << '\n';
	}
	return 2 + rows * cols;
}

void generate(int* ptr) {
	ifstream file(FILE_MATRICES);
	int offset = getFromFile(file, ptr, 0);
	getFromFile(file, ptr, offset);
	file.close();
}

int multiplyRowCol(int* ptr, PAIR& pair1, PAIR& pair2, PAIR& cur) {
	int res = 0;
	int offset = pair1.first * pair1.second + 2 + 2;
	for (int i = 0; i < pair1.second; i++) {
		res += (ptr[2 + cur.first*pair1.second + i] * ptr[offset + i*pair2.second + cur.second]);
	}
	return res;
}

void multiply(int* ptr) {
	PAIR pair1 = make_pair(ptr[0], ptr[1]), 
				   pair2 = make_pair(ptr[pair1.first * pair1.second + 2], ptr[pair1.first * pair1.second + 3]);
	if (pair1.second != pair2.first) {
		cout << "Ошибка умножения матриц\n";
		clearMem();
		exit(1);
		return;
	}

	MATRIX matrix(pair1.first, vector<int>(pair2.second));
	for (int i = 0; i < pair1.first; i++) {
		for (int j = 0; j < pair2.second; j++) {
			matrix[i][j] = multiplyRowCol(ptr, pair1, pair2, make_pair(i, j));
		}
	}
	ptr[0] = pair1.first;
	ptr[1] = pair2.second;
	for (int i = 0; i < ptr[0]; i++) {
		for(int j = 0; j < ptr[1]; j++) {
			ptr[2 + ptr[1]*i + j] = matrix[i][j];
		}
	}
}

void writeToFile(int* ptr) {
	ofstream out;
	out.open(RESULT);
	if (!out.is_open()) {
		out.close();
		cout << "Ошибка открытия файла\n";
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

void runProcess(const function<void(int*)> &func, int* ptr) {
	pid_t pid;
	int status;
	switch(pid=fork()) {
		case -1: {
			cerr << "Ошибка работы\n";
			exit(1);
		}
		case 0: {
			func(ptr);
			cout << "закончил " << getpid() << '\n';
			exit(0);
		}
		default:
			cout << getpid() << " ждет " << pid << endl;
			wait(&status);

	}	
}

int main() {
	int* memory = (int*)createMem();
	generateMatricesToFile(FILE_MATRICES, make_pair(ROWS1, COLS1), make_pair(ROWS2, COLS2));
	runProcess(generate, memory);
	runProcess(multiply, memory);
	runProcess(writeToFile, memory);
	clearMem();
	return 0;
}