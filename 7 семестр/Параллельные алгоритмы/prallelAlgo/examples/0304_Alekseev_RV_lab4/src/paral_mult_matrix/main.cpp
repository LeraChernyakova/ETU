#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <cstring>

#define MAT_N 2048
#define AMOUNT_P 1

class Matrix {
public:
	Matrix(int n_) {
		this->n = n_;

		std::vector<std::vector<int>> m(n_, std::vector<int>(n_, 0));
		this->mat = m;
	};

	void fillZero() {
		for(int y = 0; y < this->n; y++) {
			for(int x = 0; x < this->n; x++) {
				this->mat[y][x] = 0;
			}
		}
	};

	void fillMat() {
		int j = 1;
		for(int y = 0; y < this->n; y++) {
			for(int x = 0; x < this->n; x++) {
				this->mat[y][x] = j;
				j++;
			}
		}
	};

	void printMat() {
		for(int y = 0; y < this->n; y++) {
			for(int x = 0; x < this->n; x++) {
				std::cout << this->mat[y][x] << " ";
			}
			std::cout << std::endl;
		}
	};

	void push_el(int x, int y, int e) {
		this->mat[y][x] = e;
	};

	int get_el(int x, int y) {
		return this->mat[y][x];
	};

	int get_n() {return this->n;};

private:
	int n;
	std::vector<std::vector<int>> mat;
};

void createMatrixes(Matrix& left, Matrix& right, Matrix& result) {
	left.fillMat();
	right.fillMat();
	result.fillZero();
};

void multiply(int thread_i, int matrix_size, int block_size, Matrix& left, Matrix& right, Matrix& result) {
	int y = thread_i*block_size / MAT_N;
	int x = thread_i*block_size % MAT_N;
	
	for(int j = 0; j < block_size; j++) {
		for(int i = 0; i < MAT_N; i++) {
			//matrixes.result[y][x] += matrixes.left[y][i] * matrixes.right[i][x];
			result.push_el(x, y, result.get_el(x, y) + (left.get_el(i, y) * right.get_el(x, i)));
		}
		x++;
		if(x >= MAT_N) {
			x = 0;
			y++;
		}

	}
}

void multiplyMatrixes(Matrix& left, Matrix& right, Matrix& result) {
	int matrix_size = MAT_N * MAT_N;

	//int min_per_thread = 25;
	//int max_threads = (matrix_size+min_per_thread-1) / min_per_thread;

	int hardware_threads = std::thread::hardware_concurrency();
	//int num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	int num_threads = AMOUNT_P;

	int block_size = matrix_size / num_threads;

	std::vector<std::thread> threads(num_threads);

	for(int i = 0; i < (num_threads); i++) {
		threads[i] = std::thread(multiply, i, matrix_size, block_size, std::ref(left), std::ref(right), std::ref(result));
	}

	if(matrix_size % num_threads) {
		int y = num_threads*block_size / MAT_N;
		int x = num_threads*block_size % MAT_N;
		
		for(int j = 0; j < matrix_size % num_threads; j++) {
			for(int i = 0; i < MAT_N; i++) {
				//mat.result[y][x] += matrixes.left[y][i] * matrixes.right[i][x];
				result.push_el(x, y, result.get_el(x, y) + (left.get_el(i, y) * right.get_el(x, i)));
			}
			x++;
			if(x >= MAT_N) {
				x = 0;
				y++;
			}

		}
	}

	for(int i = 0; i < (num_threads); i++) {
		threads[i].join();
	}

};

void printResult(Matrix& mat) {
	mat.printMat();
};

int main() {

	Matrix left = Matrix(MAT_N);
	Matrix right = Matrix(MAT_N);
	Matrix result = Matrix(MAT_N);
	
	std::thread createMatThread(createMatrixes, std::ref(left), std::ref(right), std::ref(result));
	createMatThread.join();

	std::thread multiplyMatThread(multiplyMatrixes, std::ref(left), std::ref(right), std::ref(result));
	multiplyMatThread.join();
/*
	std::thread printMatThread(printResult, std::ref(result));
	printMatThread.join();
*/
	return 0;
}
