#include <iostream>
#include <thread>
#include <atomic>

#define MAT_Y 100
#define MAT_N 100
#define MAT_X 100

struct matrixes {
	int left [MAT_Y][MAT_N];
	int right [MAT_N][MAT_X];
	int result [MAT_Y][MAT_X];
};


void createMatrixes(matrixes& matrixes) {
	int j = 1;
	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < MAT_N; x++) {
			matrixes.left[y][x] = j;
			j++;
		}
	}

	j = 1;
	for(int y = 0; y < MAT_N; y++) {
		for(int x = 0; x < MAT_X; x++) {
			matrixes.right[y][x] = j;
			j++;
		}
	}
};

void multiplyMatrixes(matrixes& matrixes) {
	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < MAT_X; x++) {
			for(int i = 0; i < MAT_N; i++) {
				matrixes.result[y][x] += matrixes.left[y][i] * matrixes.right[i][x];
			}
		}
	}
};

void printResult(matrixes& matrixes) {
	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < MAT_X; x++) {
			std::cout << matrixes.result[y][x] << " ";
		}
		std::cout << std::endl;
	}
};

int main() {

	matrixes matrixes;
	
	std::thread createMatThread(createMatrixes, std::ref(matrixes));
	createMatThread.join();
	std::thread multiplyMatThread(multiplyMatrixes, std::ref(matrixes));
	multiplyMatThread.join();
	std::thread printMatThread(printResult, std::ref(matrixes));
	printMatThread.join();

	return 0;
}
