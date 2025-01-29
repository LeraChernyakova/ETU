#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <cstring>

#define MAT_N 1024
#define AMOUNT_TASKS 1

class Matrix {
public:
	Matrix(int n_) {
		this->n = n_;

		std::vector<std::vector<int>> m(n_, std::vector<int>(n_, 0));
		this->mat = m;
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


void printResult(Matrix& result) {
	result.printMat();
};

void createMatrixes(Matrix& left, Matrix& right, Matrix& result) {
	left.fillMat();
	right.fillMat();
	result.fillMat();
};

Matrix sumMat(Matrix left, Matrix right) {
	int n = left.get_n();
	Matrix result = Matrix(n);

	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			result.push_el(x, y, left.get_el(x, y) + right.get_el(x, y));
		}
	}

	return result;
};

Matrix subMat(Matrix left, Matrix right) {
	int n = left.get_n();
	Matrix result = Matrix(n);

	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			result.push_el(x, y, left.get_el(x, y) - right.get_el(x, y));
		}
	}

	return result;
};

int newSize(int n) {
	int new_size = 1;
	while(new_size < n) {
		new_size *= 2;
	}
	return new_size;
};

void matToStrassenMat(Matrix& left, Matrix& right, Matrix& s_left, Matrix& s_right) {
	for (int y = 0; y < MAT_N; y++) {
		for (int x = 0; x < MAT_N; x++) {
			s_left.push_el(x, y, left.get_el(x, y));
		}
	}

	for (int y = 0; y < MAT_N; y++) {
		for (int x = 0; x < MAT_N; x++) {
			s_right.push_el(x, y, right.get_el(x, y));
		}
	}
};

std::vector<Matrix> splitMat(Matrix& mat) {
	std::vector<Matrix> mats;

	int n = mat.get_n() >> 1;

	mats.push_back(Matrix(n));
	mats.push_back(Matrix(n));
	mats.push_back(Matrix(n));
	mats.push_back(Matrix(n));

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			mats[0].push_el(x, y, mat.get_el(x, y));
			mats[1].push_el(x, y, mat.get_el(x+n, y));
			mats[2].push_el(x, y, mat.get_el(x, y+n));
			mats[3].push_el(x, y, mat.get_el(x+n, y+n));
		}
	}

	return mats;
};

Matrix collectMat(Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22) {
	int n = a11.get_n();
	Matrix mat = Matrix(n * 2);

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			mat.push_el(x, y, a11.get_el(x, y));
			mat.push_el(x+n, y, a12.get_el(x, y));
			mat.push_el(x, y+n, a21.get_el(x, y));
			mat.push_el(x+n, y+n, a22.get_el(x, y));
		}
	}

	return mat;
};

Matrix multiStrassenPar(Matrix& left, Matrix& right, int n) {
	if(n <= 1) {
		Matrix result = Matrix(n);
		result.push_el(0, 0, left.get_el(0, 0) * right.get_el(0, 0));
		return result;
	};

	n = n >> 1;

	std::vector<Matrix> l_mats = splitMat(left);
	std::vector<Matrix> r_mats = splitMat(right);

	Matrix a03Sum = sumMat(l_mats[0], l_mats[3]);
	Matrix b03Sum = sumMat(r_mats[0], r_mats[3]);
	Matrix a23Sum = sumMat(l_mats[2], l_mats[3]);
	Matrix b13Sub = subMat(r_mats[1], r_mats[3]);
	Matrix b20Sub = subMat(r_mats[2], r_mats[0]);
	Matrix a01Sum = sumMat(l_mats[0], l_mats[1]);
	Matrix a20Sub = subMat(l_mats[2], l_mats[0]);
	Matrix b01Sum = sumMat(r_mats[0], r_mats[1]);
	Matrix a13Sub = subMat(l_mats[1], l_mats[3]);
	Matrix b23Sum = sumMat(r_mats[2], r_mats[3]);

	Matrix p1 = multiStrassenPar(a03Sum, b03Sum, n);
	Matrix p2 = multiStrassenPar(a23Sum, r_mats[0], n);
	Matrix p3 = multiStrassenPar(l_mats[0], b13Sub, n);
	Matrix p4 = multiStrassenPar(l_mats[3], b20Sub, n);
	Matrix p5 = multiStrassenPar(a01Sum, r_mats[3], n);
	Matrix p6 = multiStrassenPar(a20Sub, b01Sum, n);
	Matrix p7 = multiStrassenPar(a13Sub, b23Sum, n);

	Matrix p14 = sumMat(p1, p4);
	Matrix p75 = subMat(p7, p5);
	Matrix p12 = subMat(p1, p2);
	Matrix p36 = sumMat(p3, p6);

	Matrix c11 = sumMat(p14, p75);
	Matrix c12 = sumMat(p3, p5);
	Matrix c21 = sumMat(p2, p4);
	Matrix c22 = sumMat(p12, p36);

	return collectMat(c11, c12, c21, c22);
};

void multiStrassen(Matrix& res, Matrix left, Matrix right, int n, int rec) {
	if(n <= 1) {
		Matrix result = Matrix(n);
		result.push_el(0, 0, left.get_el(0, 0) * right.get_el(0, 0));
		res = result;
	} else {
		n = n >> 1;

		std::vector<Matrix> l_mats = splitMat(left);
		std::vector<Matrix> r_mats = splitMat(right);

		Matrix p1 = Matrix(n);
		Matrix p2 = Matrix(n);
		Matrix p3 = Matrix(n);
		Matrix p4 = Matrix(n);
		Matrix p5 = Matrix(n);
		Matrix p6 = Matrix(n);
		Matrix p7 = Matrix(n);

		Matrix a03Sum = sumMat(l_mats[0], l_mats[3]);
		Matrix b03Sum = sumMat(r_mats[0], r_mats[3]);
		Matrix a23Sum = sumMat(l_mats[2], l_mats[3]);
		Matrix b13Sub = subMat(r_mats[1], r_mats[3]);
		Matrix b20Sub = subMat(r_mats[2], r_mats[0]);
		Matrix a01Sum = sumMat(l_mats[0], l_mats[1]);
		Matrix a20Sub = subMat(l_mats[2], l_mats[0]);
		Matrix b01Sum = sumMat(r_mats[0], r_mats[1]);
		Matrix a13Sub = subMat(l_mats[1], l_mats[3]);
		Matrix b23Sum = sumMat(r_mats[2], r_mats[3]);

		if(rec == 0) {
			rec++;

			std::thread p1Thread(multiStrassen, std::ref(p1), std::ref(a03Sum), std::ref(b03Sum), n, rec);
			std::thread p2Thread(multiStrassen, std::ref(p2), std::ref(a23Sum), r_mats[0], n, rec);
			std::thread p3Thread(multiStrassen, std::ref(p3), l_mats[0], std::ref(b13Sub), n, rec);
			std::thread p4Thread(multiStrassen, std::ref(p4), l_mats[3], std::ref(b20Sub), n, rec);
			std::thread p5Thread(multiStrassen, std::ref(p5), std::ref(a01Sum), r_mats[3], n, rec);
			std::thread p6Thread(multiStrassen, std::ref(p6), std::ref(a20Sub), std::ref(b01Sum), n, rec);
			std::thread p7Thread(multiStrassen, std::ref(p7), std::ref(a13Sub), std::ref(b23Sum), n, rec);
			
			p1Thread.join();
			p2Thread.join();
			p3Thread.join();
			p4Thread.join();
			p5Thread.join();
			p6Thread.join();
			p7Thread.join();
		} else {
			rec++;

			p1 = multiStrassenPar(a03Sum, b03Sum, n);
			p2 = multiStrassenPar(a23Sum, r_mats[0], n);
			p3 = multiStrassenPar(l_mats[0], b13Sub, n);
			p4 = multiStrassenPar(l_mats[3], b20Sub, n);
			p5 = multiStrassenPar(a01Sum, r_mats[3], n);
			p6 = multiStrassenPar(a20Sub, b01Sum, n);
			p7 = multiStrassenPar(a13Sub, b23Sum, n);
		}	

		rec--;

		Matrix c11 = sumMat(sumMat(p1, p4), subMat(p7, p5));
		Matrix c12 = sumMat(p3, p5);
		Matrix c21 = sumMat(p2, p4);
		Matrix c22 = sumMat(subMat(p1, p2), sumMat(p3, p6));

		res = collectMat(c11, c12, c21, c22);
	}
};


Matrix strassen(Matrix& left, Matrix& right) {
	int n = left.get_n();
	int new_size = newSize(n);

	Matrix s_left = Matrix(new_size);
	Matrix s_right = Matrix(new_size);
	Matrix result = Matrix(n);

	matToStrassenMat(left, right, s_left, s_right);

	Matrix strasMat = Matrix(new_size);
	multiStrassen(strasMat, s_left, s_right, new_size, 0);

	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			result.push_el(x, y, strasMat.get_el(x, y));
		}
	}

	return result;
};

int main() {

	Matrix left = Matrix(MAT_N);
	Matrix right = Matrix(MAT_N);
	Matrix result = Matrix(MAT_N);

	for(int i = 0; i < AMOUNT_TASKS; i++) {
		createMatrixes(left, right, result);
		result = strassen(left, right);
		//printResult(result);
	}

	return 0;
}
