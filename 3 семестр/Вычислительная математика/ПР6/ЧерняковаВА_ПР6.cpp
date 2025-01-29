#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>

const int matrix_side = 4;

const std::vector<double> matrix = {1,  2, -1, 3,
                                    5, -4,  3, 7,
                                    4, 6, 3, 0,
                                    2, 8, 1, -5};

const std::vector<double> gilbert_matrix = {1,  2, -1, 3,
                                    1/2.0, 1/3.0,  1/4.0, 1/5.0,
                                    4, 6, 3, 0,
                                    1/4.0, 1/5.0, 1/6.0, 1/7.0};

const std::vector<double> vectorB = {0, 26, -8, 3};


std::vector<double> GaussMethod(std::vector<double> m, std::vector<double> b){
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

std::vector<double> getInverseMatrix(std::vector<double> m){//через единичную матрицу
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

std::vector<double> ReverseMethod(std::vector<double> inv, std::vector<double> b){
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

double cond(const std::vector<double>& m, const std::vector<double>& inv){
	return matrixNorm(m) * matrixNorm(inv);
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
	new_vector.push_back(0.0118);
	new_vector.push_back(25.9390);
	new_vector.push_back(-8.0950);
	new_vector.push_back(3.0402);
	return new_vector;
}

std::vector<double> setInaccuracyInVector2(const std::vector<double>& v){
	std::srand(std::time(NULL) + reinterpret_cast<size_t>(&v));
	double inaccuracy;
	std::vector<double> new_vector;/*
	new_vector.reserve(v.size());
	for (const double& x: v){
		inaccuracy = (std::rand() % 1000 - 500) / 5000.0; // [-0.1; 0.1]
		new_vector.push_back(x + inaccuracy);
	}*/
	new_vector.push_back(-0.0602);
	new_vector.push_back(26.0146);
	new_vector.push_back(-8.0774);
	new_vector.push_back(2.9560);
	return new_vector;
}

double vectorNorm(const std::vector<double>& v){
	double norm = std::fabs(v.at(0));
	for (int i = 0; i < matrix_side; ++i)
		if (std::fabs(v.at(i)) > norm)
            norm = std::fabs(v.at(i));
	return norm;
}

double AbsoluteAccuracyVector(const std::vector<double>& v, const std::vector<double>& in){
	std::vector<double> delta;
	delta.resize(v.size());
	for (int i = 0; i < v.size(); ++i)
		delta.at(i) = v.at(i) - in.at(i);
	return vectorNorm(delta);
}

double relativeInaccuracyVector(const std::vector<double>& v, const std::vector<double>& in){
	std::vector<double> delta;
	delta.resize(v.size());
	for (int i = 0; i < v.size(); ++i)
		delta.at(i) = v.at(i) - in.at(i);
	return vectorNorm(delta) / vectorNorm(v);
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
	new_vector.push_back(1.0602);
	new_vector.push_back(2.0362);
	new_vector.push_back(-0.9650);
	new_vector.push_back(3.0072);
	new_vector.push_back(5.0288);
	new_vector.push_back(-4.0302);
	new_vector.push_back(2.9908);
	new_vector.push_back(7.0284);
	new_vector.push_back(4.0982);
	new_vector.push_back(5.9694);
	new_vector.push_back(2.9730);
	new_vector.push_back(-0.0374);
	new_vector.push_back(2.0030);
	new_vector.push_back(8.0366);
	new_vector.push_back(1.0328);
	new_vector.push_back(-5.0718);
	return new_vector;
}

std::vector<double> setInaccuracyInMatrix2(const std::vector<double>& m){
	std::srand(std::time(NULL) + reinterpret_cast<size_t>(&m));
	double inaccuracy;
	std::vector<double> new_vector;/*
	new_vector.reserve(m.size());
	for (const double& x: m){
		inaccuracy = (std::rand() % 1000 - 500) / 5000.0; // [-0.1; 0.1]
		new_vector.push_back(x + inaccuracy);
	}*/
	new_vector.push_back(1.0810);
	new_vector.push_back(1.9364);
	new_vector.push_back(-1.0456);
	new_vector.push_back(2.9260);
	new_vector.push_back(0.4060);
	new_vector.push_back(0.4199);
	new_vector.push_back(0.2998);
	new_vector.push_back(0.1546);
	new_vector.push_back(3.9146);
	new_vector.push_back(5.9432);
	new_vector.push_back(3.0264);
	new_vector.push_back(0.0444);
	new_vector.push_back(0.3162);
	new_vector.push_back(0.2754);
	new_vector.push_back(0.2501);
	new_vector.push_back(0.2237);
	return new_vector;
}

double AbsoluteAccuracyMatrix(const std::vector<double>& m, const std::vector<double>& in){
	std::vector<double> delta;
	delta.resize(m.size());
	for (int i = 0; i < m.size(); ++i)
		delta.at(i) = m.at(i) - in.at(i);
	return matrixNorm(delta);
}

double relativeInaccuracyMatrix(const std::vector<double>& m, const std::vector<double>& in){
	std::vector<double> delta;
	delta.resize(m.size());
	for (int i = 0; i < m.size(); ++i)
		delta.at(i) = m.at(i) - in.at(i);
	return matrixNorm(delta) / matrixNorm(m);
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

int main(){
    setlocale(LC_ALL, "Russian");

    //пункт 1
    std::vector<double> solutionG = GaussMethod(matrix, vectorB);
	std::vector<double> solutionI = ReverseMethod(getInverseMatrix(matrix), vectorB);
	std::cout << std::fixed;
	std::cout << std::setprecision(4);
	std::cout << "!Решение системы без внесения погрешностей!" << std::endl;
	std::cout << "1)Исходная матрица" << std::endl;
	printMatrix(matrix);
	std::cout << "Обратная ей матрица" << std::endl;
	printMatrix(getInverseMatrix(matrix));
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(solutionG);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(solutionI);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) * vectorNorm(vectorB) / vectorNorm(solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(matrix, getInverseMatrix(matrix)) << std::endl;
	std::cout << std::endl;


    std::vector<double> solutionG_g = GaussMethod(gilbert_matrix, vectorB);
	std::vector<double> solutionI_g = ReverseMethod(getInverseMatrix(gilbert_matrix), vectorB);
    std::cout << "2)Матрица Гильберта" << std::endl;
	printMatrix(gilbert_matrix);
    std::cout << "Обратная ей матрица" << std::endl;
	printMatrix(getInverseMatrix(gilbert_matrix));
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(solutionG_g);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(solutionI_g);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(gilbert_matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(gilbert_matrix)) * vectorNorm(vectorB) / vectorNorm(solutionG_g) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
    std::cout << matrixNorm(getInverseMatrix(gilbert_matrix))<<std::endl;

	//пункт 2
	std::vector<double> in_vectorB = setInaccuracyInVector1(vectorB);
    std::vector<double> in2_solutionG = GaussMethod(matrix, in_vectorB);
	std::vector<double> in2_solutionI = ReverseMethod(getInverseMatrix(matrix), in_vectorB);
	std::cout << "!Решение системы с внесением погрешностей в вектор свободных членов!" << std::endl;
	std::cout << "1)Исходная матрица" << std::endl;
	printMatrix(matrix);
	std::cout << "Вектор B до возмущения" << std::endl;
	printVector(vectorB);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(in2_solutionG);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(in2_solutionI);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(matrix)) * vectorNorm(in_vectorB) / vectorNorm(in2_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(matrix, getInverseMatrix(matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы(дельта(X*)/дельта(B*))" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in2_solutionG) / relativeInaccuracyVector(vectorB, in_vectorB) << std::endl;
	std::cout << std::endl;
    std::cout << "Абсолютная погрешность вектора X" << std::endl;
	std::cout << AbsoluteAccuracyVector(solutionG, in2_solutionG)<<std::endl;
	std::cout << "Относительная погрешность вектора X" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in2_solutionG)<<std::endl;
    std::cout << "Абсолютная погрешность вектора B" << std::endl;
	std::cout << AbsoluteAccuracyVector(vectorB, in_vectorB)<<std::endl;
	std::cout << "Относительная погрешность вектора B" << std::endl;
	std::cout << relativeInaccuracyVector(vectorB, in_vectorB)<<std::endl;

    std::vector<double> in_vectorB_g = setInaccuracyInVector2(vectorB);
    std::vector<double> in2_solutionG_g = GaussMethod(gilbert_matrix, in_vectorB_g);
	std::vector<double> in2_solutionI_g = ReverseMethod(getInverseMatrix(gilbert_matrix), in_vectorB_g);
	std::cout << "2)Матрица Гильберта" << std::endl;
	printMatrix(matrix);
	std::cout << "Вектор B до возмущения" << std::endl;
	printVector(vectorB);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB_g);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(in2_solutionG_g);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(in2_solutionI_g);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(gilbert_matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(gilbert_matrix)) * vectorNorm(in_vectorB_g) / vectorNorm(in2_solutionG_g) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(gilbert_matrix, getInverseMatrix(gilbert_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы(дельта(X*)/дельта(B*))" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG_g, in2_solutionG_g) / relativeInaccuracyVector(vectorB, in_vectorB_g) << std::endl;
	std::cout << std::endl;
    std::cout << "Абсолютная погрешность вектора X" << std::endl;
	std::cout << AbsoluteAccuracyVector(solutionG_g, in2_solutionG_g)<<std::endl;
	std::cout << "Относительная погрешность вектора X" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG_g, in2_solutionG_g)<<std::endl;
    std::cout << "Абсолютная погрешность вектора B" << std::endl;
	std::cout << AbsoluteAccuracyVector(vectorB, in_vectorB_g)<<std::endl;
	std::cout << "Относительная погрешность вектора B" << std::endl;
	std::cout << relativeInaccuracyVector(vectorB, in_vectorB_g)<<std::endl;

	//пункт 3
	std::cout << "!Решение системы с внесением погрешностей в матрицу системы!" << std::endl;
	std::vector<double> in_matrix = setInaccuracyInMatrix1(matrix);
    std::vector<double> in1_solutionG = GaussMethod(in_matrix, vectorB);
	std::vector<double> in1_solutionI = ReverseMethod(getInverseMatrix(in_matrix), vectorB);
	std::cout << "1)Исходная матрица"<<std::endl;
	printMatrix(matrix);
	std::cout << "Возумущенная исходная матрица системы" << std::endl;
	printMatrix(in_matrix);
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(in1_solutionG);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(in1_solutionI);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix)) * vectorNorm(vectorB) / vectorNorm(in1_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix, getInverseMatrix(in_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы(дельта Xдельта A*)" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in1_solutionG) / relativeInaccuracyMatrix(matrix, in_matrix) << std::endl;
	std::cout << std::endl;
    std::cout << "Абсолютная погрешность вектора X" << std::endl;
	std::cout << AbsoluteAccuracyVector(solutionG, in1_solutionG)<<std::endl;
	std::cout << "Относительная погрешность вектора X" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in2_solutionG)<<std::endl;
    std::cout << "Абсолютная погрешность матрицы A" << std::endl;
	std::cout << AbsoluteAccuracyMatrix(matrix, in_matrix)<<std::endl;
	std::cout << "Относительная погрешность матрицы A" << std::endl;
	std::cout << relativeInaccuracyMatrix(matrix, in_matrix)<<std::endl;

    std::vector<double> in_matrix_g = setInaccuracyInMatrix2(gilbert_matrix);
    std::vector<double> in1_solutionG_g = GaussMethod(in_matrix_g, vectorB);
	std::vector<double> in1_solutionI_g = ReverseMethod(getInverseMatrix(in_matrix_g), vectorB);
	std::cout << "2)Матрица Гильберта"<<std::endl;
	printMatrix(gilbert_matrix);
	std::cout << "Возумущенная матрица Гильберта" << std::endl;
	printMatrix(in_matrix_g);
	std::cout << "Исходный вектор B" << std::endl;
	printVector(vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(in1_solutionG_g);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(in1_solutionI_g);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix_g)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix_g)) * vectorNorm(in_vectorB_g) / vectorNorm(in1_solutionG_g) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix_g, getInverseMatrix(in_matrix_g)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы(дельта (X*)/дельта (A*))" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG_g, in1_solutionG_g) / relativeInaccuracyMatrix(gilbert_matrix, in_matrix_g) << std::endl;
	std::cout << std::endl;
    std::cout << "Абсолютная погрешность вектора X" << std::endl;
	std::cout << AbsoluteAccuracyVector(solutionG_g, in1_solutionG_g)<<std::endl;
	std::cout << "Относительная погрешность вектора X" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG_g, in1_solutionG_g)<<std::endl;
    std::cout << "Абсолютная погрешность матрицы A" << std::endl;
	std::cout << AbsoluteAccuracyMatrix(gilbert_matrix, in_matrix_g)<<std::endl;
	std::cout << "Относительная погрешность матрицы A" << std::endl;
	std::cout << relativeInaccuracyMatrix(gilbert_matrix, in_matrix_g)<<std::endl;

	//пункт 4
    std::cout << "!Решение системы с внесением погрешностей в матрицу и вектор B!" << std::endl;
    std::vector<double> in3_solutionG = GaussMethod(in_matrix, in_vectorB);
	std::vector<double> in3_solutionI = ReverseMethod(getInverseMatrix(in_matrix), in_vectorB);
    std::cout << "1)Исходная матрица"<<std::endl;
	printMatrix(matrix);
    std::cout << "Возумущенная матрица системы" << std::endl;
	printMatrix(in_matrix);
    std::cout << "Вектор B до возмущения" << std::endl;
	printVector(vectorB);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(in3_solutionG);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(in3_solutionI);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix)) * vectorNorm(in_vectorB) / vectorNorm(in3_solutionG) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix, getInverseMatrix(in_matrix)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы(дельта (X*)/(дельта A* + дельта B*))" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in3_solutionG) / (relativeInaccuracyVector(vectorB, in_vectorB) +
	relativeInaccuracyMatrix(matrix, in_matrix)) << std::endl;
	std::cout << std::endl;
    std::cout << "Абсолютная погрешность вектора X" << std::endl;
	std::cout << AbsoluteAccuracyVector(solutionG, in3_solutionG)<<std::endl;
	std::cout << "Относительная погрешность вектора X" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG, in3_solutionG)<<std::endl;
    std::cout << "Абсолютная погрешность вектора B" << std::endl;
	std::cout << AbsoluteAccuracyVector(vectorB, in_vectorB)<<std::endl;
	std::cout << "Относительная погрешность вектора B" << std::endl;
	std::cout << relativeInaccuracyVector(vectorB, in_vectorB)<<std::endl;
    std::cout << "Абсолютная погрешность матрицы A" << std::endl;
	std::cout << AbsoluteAccuracyMatrix(matrix, in_matrix)<<std::endl;
	std::cout << "Относительная погрешность матрицы A" << std::endl;
	std::cout << relativeInaccuracyMatrix(matrix, in_matrix)<<std::endl;

    std::vector<double> in3_solutionG_g = GaussMethod(in_matrix_g, in_vectorB_g);
	std::vector<double> in3_solutionI_g = ReverseMethod(getInverseMatrix(in_matrix_g), in_vectorB_g);
    std::cout << "2)Матрица Гильберта"<<std::endl;
	printMatrix(gilbert_matrix);
    std::cout << "Возумущенная матрица Гильберта системы" << std::endl;
	printMatrix(in_matrix_g);
    std::cout << "Вектор B до возмущения" << std::endl;
	printVector(vectorB);
	std::cout << "Возумущенный вектор B" << std::endl;
	printVector(in_vectorB_g);
	std::cout << std::endl;
	std::cout << "Метод Гаусса" << std::endl;
	printVector(in3_solutionG_g);
	std::cout << "Метод обратной матрицы" << std::endl;
	printVector(in3_solutionI_g);
	std::cout << std::endl;
    std::cout << "Абсолютное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix_g)) << std::endl;
	std::cout << std::endl;
    std::cout << "Естественное число обусловленности системы" << std::endl;
	std::cout << matrixNorm(getInverseMatrix(in_matrix_g)) * vectorNorm(in_vectorB_g) / vectorNorm(in3_solutionG_g) << std::endl;
	std::cout << std::endl;
	std::cout << "Стандартное число обусловленности системы" << std::endl;
	std::cout << cond(in_matrix_g, getInverseMatrix(in_matrix_g)) << std::endl;
	std::cout << "Оценка стандартного числа обусловленности системы(дельта (X*)/(дельта A* + дельта B*))" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG_g, in3_solutionG_g) / (relativeInaccuracyVector(vectorB, in_vectorB_g) +
	relativeInaccuracyMatrix(gilbert_matrix, in_matrix_g)) << std::endl;
    std::cout << "Абсолютная погрешность вектора X" << std::endl;
	std::cout << AbsoluteAccuracyVector(solutionG_g, in3_solutionG_g)<<std::endl;
	std::cout << "Относительная погрешность вектора X" << std::endl;
	std::cout << relativeInaccuracyVector(solutionG_g, in3_solutionG_g)<<std::endl;
    std::cout << "Абсолютная погрешность вектора B" << std::endl;
	std::cout << AbsoluteAccuracyVector(vectorB, in_vectorB_g)<<std::endl;
	std::cout << "Относительная погрешность вектора B" << std::endl;
	std::cout << relativeInaccuracyVector(vectorB, in_vectorB_g)<<std::endl;
    std::cout << "Абсолютная погрешность матрицы A" << std::endl;
	std::cout << AbsoluteAccuracyMatrix(gilbert_matrix, in_matrix_g)<<std::endl;
	std::cout << "Относительная погрешность матрицы A" << std::endl;
	std::cout << relativeInaccuracyMatrix(gilbert_matrix, in_matrix_g)<<std::endl;
	std::cout << std::endl;
}
