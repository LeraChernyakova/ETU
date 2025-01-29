#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#define MAT_Y 150
#define MAT_N 150
#define MAT_X 150
#define AMOUNT_P 64

struct matrixes {
	int left [MAT_Y][MAT_N];
	int right [MAT_N][MAT_X];
	int result [MAT_Y][MAT_X];
};

void createMatrixes(matrixes& matrixes) {
	int j = 1;
	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < 6; x++) {
			matrixes.left[y][x] = j;
			j++;
		}
	}

	j = 1;
	for(int y = 0; y < 6; y++) {
		for(int x = 0; x < 7; x++) {
			matrixes.right[y][x] = j;
			j++;
		}
	}
};

void multiply(int thread_i, int matrix_size, int block_size, matrixes& matrixes) {
	int y = thread_i*block_size / MAT_X;
	int x = thread_i*block_size % MAT_X;
	
	for(int j = 0; j < block_size; j++) {
		for(int i = 0; i < MAT_N; i++) {
			matrixes.result[y][x] += matrixes.left[y][i] * matrixes.right[i][x];
		}
		x++;
		if(x >= MAT_X) {
			x = 0;
			y++;
		}

	}
}

void multiplyMatrixes(matrixes& matrixes) {
	int matrix_size = MAT_X * MAT_Y;
	//int min_per_thread = 25;
	//int max_threads = (matrix_size+min_per_thread-1) / min_per_thread;

	int hardware_threads = std::thread::hardware_concurrency();
	//int num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	int num_threads = AMOUNT_P;

	int block_size = matrix_size / num_threads;

	std::vector<std::thread> threads(num_threads);

	for(int i = 0; i < (num_threads); i++) {
		threads[i] = std::thread(multiply, i, matrix_size, block_size, std::ref(matrixes));
	}

	if(matrix_size % num_threads) {
		int y = num_threads*block_size / MAT_X;
		int x = num_threads*block_size % MAT_X;
		
		for(int j = 0; j < matrix_size % num_threads; j++) {
			for(int i = 0; i < MAT_N; i++) {
				matrixes.result[y][x] += matrixes.left[y][i] * matrixes.right[i][x];
			}
			x++;
			if(x >= MAT_X) {
				x = 0;
				y++;
			}

		}
	}

	for(int i = 0; i < (num_threads); i++) {
		threads[i].join();
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
