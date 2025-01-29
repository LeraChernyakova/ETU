#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>

void calculate1(const std::vector<double>& matrix, const::std::vector<double>& vectorB);
void calculate2(const std::vector<double>& matrix, const::std::vector<double>& vectorB);
void printMatrix(const std::vector<double>& m);
void printVector(const std::vector<double>& v);
std::vector<double> gaussianMethod(std::vector<double> m, std::vector<double> b);
std::vector<double> inverseMatrixMethod(std::vector<double> inv, std::vector<double> b);
std::vector<double> getInverseMatrix(std::vector<double> m);
double vectorNorm(const std::vector<double>& v);
double matrixNorm(const std::vector<double>& m);
std::vector<double> setInaccuracyInVector1(const std::vector<double>& v);
std::vector<double> setInaccuracyInMatrix1(const std::vector<double>& m);
std::vector<double> setInaccuracyInVector2(const std::vector<double>& v);
std::vector<double> setInaccuracyInMatrix2(const std::vector<double>& m);
double cond(const std::vector<double>& m, const std::vector<double>& inv);
double relativeInaccuracyVector(const std::vector<double>& v, const std::vector<double>& in);
double relativeInaccuracyMatrix(const std::vector<double>& m, const std::vector<double>& in);
const int matrix_side = 3;
const std::vector<double> __matrix = {3,  1, -4,
									  2, -3,  5,
									  6, -2, -3
};
const std::vector<double> __gilbertMatrix = {1, 1 / 2.0, -4,
									         1 / 2.0, 1 / 3.0, 5,
									         1 / 3.0, 1 / 4.0, -3
};
const std::vector<double> __vectorB = {13, -10, 9};
const std::vector<double> __inverseMatrix = {19/37.0, 11/37.0, -7/37.0,
									         36/37.0, 15/37.0, -23/37.0,
									         14/37.0, 12/37.0, -11/37.0
};

int main(){
	calculate1(__matrix, __vectorB);
	calculate2(__gilbertMatrix, __vectorB);
	return 0;
}

void calculate1(const std::vector<double>& matrix, const::std::vector<double>& vectorB){
	std::vector<double> solutionG = gaussianMethod(matrix, vectorB);
	std::vector<double> solutionI = inverseMatrixMethod(getInverseMatrix(matrix), vectorB);
	std::vector<double> in_matrix = setInaccuracyInMatrix1(matrix);
	std::vector<double> in_vectorB = setInaccuracyInVector1(vectorB);
	std::vector<double> in1_solutionG = gaussianMethod(in_matrix, vectorB);
	std::vector<double> in1_solutionI = inverseMatrixMethod(getInverseMatrix(in_matrix), vectorB);
	std::vector<double> in2_solutionG = gaussianMethod(matrix, in_vectorB);
	std::vector<double> in2_solutionI = inverseMatrixMethod(getInverseMatrix(matrix), in_vectorB);
	std::vector<double> in3_solutionG = gaussianMethod(in_matrix, in_vectorB);
	std::vector<double> in3_solutionI = inverseMatrixMethod(getInverseMatrix(in_matrix), in_vectorB);
	std::cout << std::fixed;
	std::cout << std::setprecision(4);
	std::cout << "----- Решение системы без внесения погрешностей -----" << std::endl;
	std::cout << "Исходная матрица" << std::endl;
	printMatrix(matrix);
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(solutionG);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(matrix, getInverseMatrix(matrix)) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) * vectorNorm(vectorB) / vectorNorm(solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "----- Решение системы с внесением погрешностей в матрицу системы -----" << std::endl;
	std::cout << "Возумущенная матрица системы" << std::endl;
	printMatrix(in_matrix);
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Вектор-решение методом Гаусса" << std::endl;
	printVector(in1_solutionG);
	std::cout << "Вектор-решение методом обратной матрицы" << std::endl;
	printVector(in1_solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix, getInverseMatrix(in_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in1_solutionG) / relativeInaccuracyMatrix(matrix, in_matrix) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix)) * vectorNorm(vectorB) / vectorNorm(in1_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "----- Решение системы с внесением погрешностей в вектор B -----" << std::endl;
	std::cout << "Исходная матрица" << std::endl;
	printMatrix(matrix);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB);
	std::cout << std::endl;
	std::cout << "Вектор-решение методом Гаусса" << std::endl;
	printVector(in2_solutionG);
	std::cout << "Вектор-решение методом обратной матрицы" << std::endl;
	printVector(in2_solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(matrix, getInverseMatrix(matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in2_solutionG) / relativeInaccuracyVector(vectorB, in_vectorB) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) * vectorNorm(vectorB) / vectorNorm(in2_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "----- Решение системы с внесением погрешностей в матрицу и вектор B -----" << std::endl;
	std::cout << "Возумущенная матрица системы" << std::endl;
	printMatrix(in_matrix);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB);
	std::cout << std::endl;
	std::cout << "Вектор-решение методом Гаусса" << std::endl;
	printVector(in3_solutionG);
	std::cout << "Вектор-решение методом обратной матрицы" << std::endl;
	printVector(in3_solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix, getInverseMatrix(in_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in3_solutionG) / (relativeInaccuracyVector(vectorB, in_vectorB) +
	relativeInaccuracyMatrix(matrix, in_matrix)) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) *
	vectorNorm(vectorB) / vectorNorm(in3_solutionG) << std::endl;
	std::cout << std::endl;
}

void calculate2(const std::vector<double>& matrix, const::std::vector<double>& vectorB){
	std::vector<double> solutionG = gaussianMethod(matrix, vectorB);
	std::vector<double> solutionI = inverseMatrixMethod(getInverseMatrix(matrix), vectorB);
	std::vector<double> in_matrix = setInaccuracyInMatrix2(matrix);
	std::vector<double> in_vectorB = setInaccuracyInVector2(vectorB);
	std::vector<double> in1_solutionG = gaussianMethod(in_matrix, vectorB);
	std::vector<double> in1_solutionI = inverseMatrixMethod(getInverseMatrix(in_matrix), vectorB);
	std::vector<double> in2_solutionG = gaussianMethod(matrix, in_vectorB);
	std::vector<double> in2_solutionI = inverseMatrixMethod(getInverseMatrix(matrix), in_vectorB);
	std::vector<double> in3_solutionG = gaussianMethod(in_matrix, in_vectorB);
	std::vector<double> in3_solutionI = inverseMatrixMethod(getInverseMatrix(in_matrix), in_vectorB);
	std::cout << std::fixed;
	std::cout << std::setprecision(4);
	std::cout << "----- Решение системы без внесения погрешностей -----" << std::endl;
	std::cout << "Исходная матрица" << std::endl;
	printMatrix(matrix);
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(solutionG);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(matrix, getInverseMatrix(matrix)) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) * vectorNorm(vectorB) / vectorNorm(solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "----- Решение системы с внесением погрешностей в матрицу системы -----" << std::endl;
	std::cout << "Возумущенная матрица системы" << std::endl;
	printMatrix(in_matrix);
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Вектор-решение методом Гаусса" << std::endl;
	printVector(in1_solutionG);
	std::cout << "Вектор-решение методом обратной матрицы" << std::endl;
	printVector(in1_solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix, getInverseMatrix(in_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in1_solutionG) / relativeInaccuracyMatrix(matrix, in_matrix) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix)) * vectorNorm(vectorB) / vectorNorm(in1_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "----- Решение системы с внесением погрешностей в вектор B -----" << std::endl;
	std::cout << "Исходная матрица" << std::endl;
	printMatrix(matrix);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB);
	std::cout << std::endl;
	std::cout << "Вектор-решение методом Гаусса" << std::endl;
	printVector(in2_solutionG);
	std::cout << "Вектор-решение методом обратной матрицы" << std::endl;
	printVector(in2_solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(matrix, getInverseMatrix(matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in2_solutionG) / relativeInaccuracyVector(vectorB, in_vectorB) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) * vectorNorm(vectorB) / vectorNorm(in2_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "----- Решение системы с внесением погрешностей в матрицу и вектор B -----" << std::endl;
	std::cout << "Возумущенная матрица системы" << std::endl;
	printMatrix(in_matrix);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB);
	std::cout << std::endl;
	std::cout << "Вектор-решение методом Гаусса" << std::endl;
	printVector(in3_solutionG);
	std::cout << "Вектор-решение методом обратной матрицы" << std::endl;
	printVector(in3_solutionI);
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix, getInverseMatrix(in_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in3_solutionG) / (relativeInaccuracyVector(vectorB, in_vectorB) +
	relativeInaccuracyMatrix(matrix, in_matrix)) << std::endl;
	std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) *
	vectorNorm(vectorB) / vectorNorm(in3_solutionG) << std::endl;
	std::cout << std::endl;
}

void printMatrix(const std::vector<double>& m){
	for (int i = 0; i < matrix_side; ++i){
		for (int j = 0; j < matrix_side; ++j){
			std::cout << std::setw(7);
			std::cout << m.at(i * matrix_side + j) << " ";
		}
		std::cout << std::endl;
	}
}

void printVector(const std::vector<double>& v){
	std::cout << "(";
	for (int i = 0; i < v.size() - 1; ++i)
		std::cout << v.at(i) << ", ";
	std::cout << v.at(v.size() - 1);
	std::cout << ")" << std::endl;
}

std::vector<double> gaussianMethod(std::vector<double> m, std::vector<double> b){
	int i, j, k;
	double nu, prime;
	for (i = 0; i < matrix_side; ++i){
		prime = m.at(i * matrix_side + i);
		for (j = 0; j < matrix_side; ++j){
			if (j == i){
				for (k = 0; k < matrix_side; ++k)
					m.at(i * matrix_side + k) /= prime;
				b.at(i) /= prime;
				continue;
			}
			nu = -m.at(j * matrix_side + i) / m.at(i * matrix_side + i);
			for (k = 0; k < matrix_side; ++k)
				m.at(j * matrix_side + k) += nu * m.at(i * matrix_side + k);
			b.at(j) += nu * b.at(i);
		}
	}
	return b;
}

std::vector<double> inverseMatrixMethod(std::vector<double> inv, std::vector<double> b){
	int i, j;
	std::vector<double> result;
	result.resize(matrix_side);
	for (i = 0; i < matrix_side; ++i){
		double element = 0;
		for (j = 0; j < matrix_side; ++j)
			element += inv.at(i * matrix_side + j) * b.at(j);
		result.at(i) = element;
	}
	return result;
}

double vectorNorm(const std::vector<double>& v){
	double norm = 0;
	for (int i = 0; i < matrix_side; ++i)
		norm += std::fabs(v.at(i));
	return norm;
}

double matrixNorm(const std::vector<double>& m){
	double norm = 0, _norm = 0;
	for (int j = 0; j < matrix_side; ++j){
		_norm = 0;
		for (int i = 0; i < matrix_side; ++i){
			_norm += std::fabs(m.at(i * matrix_side + j));
		}
		norm = norm > _norm ? norm : _norm;
	}
	return norm;
}

std::vector<double> setInaccuracyInVector1(const std::vector<double>& v){
	std::srand(std::time(NULL) + reinterpret_cast<size_t>(&v));
	double inaccuracy;
	std::vector<double> new_vector;/*
	new_vector.reserve(v.size());
	for (const double& x: v){
		inaccuracy = (std::rand() % 1000 - 500) / 5000.0; // [-0.1; 0.1]
		new_vector.push_back(x + inaccuracy);
	}*/
	new_vector.push_back(12.9624);
	new_vector.push_back(-9.9740);
	new_vector.push_back(9.0908);
	return new_vector;
}

std::vector<double> setInaccuracyInMatrix1(const std::vector<double>& m){
	std::srand(std::time(NULL) + reinterpret_cast<size_t>(&m));
	double inaccuracy;
	std::vector<double> new_vector;/*
	new_vector.reserve(m.size());
	for (const double& x: m){
		inaccuracy = (std::rand() % 1000 - 500) / 5000.0; // [-0.1; 0.1]
		new_vector.push_back(x + inaccuracy);
	}*/
	new_vector.push_back(2.9116);
	new_vector.push_back(0.9232);
	new_vector.push_back(-3.9032);
	new_vector.push_back(2.0410);
	new_vector.push_back(-2.9088);
	new_vector.push_back(5.0214);
	new_vector.push_back(6.0686);
	new_vector.push_back(-2.0258);
	new_vector.push_back(-3.0278);
	return new_vector;
}

std::vector<double> setInaccuracyInVector2(const std::vector<double>& v){
	std::srand(std::time(NULL) + reinterpret_cast<size_t>(&v));
	double inaccuracy;
	std::vector<double> new_vector;
	new_vector.push_back(13.0864);
	new_vector.push_back(-9.9944);
	new_vector.push_back(9.0022);
	return new_vector;
}

std::vector<double> setInaccuracyInMatrix2(const std::vector<double>& m){
	std::srand(std::time(NULL) + reinterpret_cast<size_t>(&m));
	double inaccuracy;
	std::vector<double> new_vector;
	new_vector.push_back(0.9830);
	new_vector.push_back(0.5240);
	new_vector.push_back(-4.0348);
	new_vector.push_back(0.4298);
	new_vector.push_back(0.3309);
	new_vector.push_back(4.9626);
	new_vector.push_back(0.3179);
	new_vector.push_back(0.2746);
	new_vector.push_back(-2.9872);
	return new_vector;
}

std::vector<double> getInverseMatrix(std::vector<double> m){
	std::vector<double> inverse;
	inverse.resize(matrix_side * matrix_side);
	for (int i = 0; i < matrix_side; ++i)
		inverse.at(i * matrix_side + i) = 1;
	int i, j, k;
	double nu, prime;
	for (i = 0; i < matrix_side; ++i){
		prime = m.at(i * matrix_side + i);
		for (j = 0; j < matrix_side; ++j){
			if (j == i){
				for (k = 0; k < matrix_side; ++k){
					m.at(i * matrix_side + k) /= prime;
					inverse.at(i * matrix_side + k) /= prime;
				}
				continue;
			}
			nu = -m.at(j * matrix_side + i) / m.at(i * matrix_side + i);
			for (k = 0; k < matrix_side; ++k){
				m.at(j * matrix_side + k) += nu * m.at(i * matrix_side + k);
				inverse.at(j * matrix_side + k) += nu * inverse.at(i * matrix_side + k);
			}
		}
	}
	return inverse;
}

double cond(const std::vector<double>& m, const std::vector<double>& inv){
	return matrixNorm(m) * matrixNorm(inv);
}

double relativeInaccuracyVector(const std::vector<double>& v, const std::vector<double>& in){
	std::vector<double> delta;
	delta.resize(v.size());
	for (int i = 0; i < v.size(); ++i)
		delta.at(i) = v.at(i) - in.at(i);
	return vectorNorm(delta) / vectorNorm(v);
}
	
double relativeInaccuracyMatrix(const std::vector<double>& m, const std::vector<double>& in){
	std::vector<double> delta;
	delta.resize(m.size());
	for (int i = 0; i < m.size(); ++i)
		delta.at(i) = m.at(i) - in.at(i);
	return matrixNorm(delta) / matrixNorm(m);
}