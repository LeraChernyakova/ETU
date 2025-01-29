#include "./matrix.h"
#include "./handler.h"
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

#define MAT_Y 10
#define MAT_N 10
#define MAT_X 10

#define AMOUNT_PROD 100
#define AMOUNT_CONS 100
#define AMOUNT_TASK 10000

std::atomic_int tasksToComplete{0};
std::atomic_int outputMatrixLeft{0};

Matrix createMatrix(int rows, int cols)
{
	Matrix newMatrix(rows, cols);
	int j = 1;
	
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			newMatrix.getElem(r, c) = j;
			j++;
		}
	}

	return newMatrix;
}

void printMatrix(const Matrix& matrix)
{
	for(int r = 0; r < matrix.getRows(); r++){
		for(int c = 0; c < matrix.getCols(); c++){
			std::cout << matrix.getElem(r, c) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void producer(Handler<std::pair<Matrix, Matrix>>& matrixPair, 
	int threadNum, int taskCount)
{
	for(int i = 0; i < taskCount; i++) {
		matrixPair.push({createMatrix(MAT_Y, MAT_N), createMatrix(MAT_N, MAT_X)}, threadNum);
	}
}

void consumer(Handler<std::pair<Matrix, Matrix>>& matrixPair, 
	Handler<Matrix>& outputMatrixes, int threadNumMP, int threadNumO)
{
	std::pair<Matrix, Matrix> task;
	while(tasksToComplete > 0) {
		if(matrixPair.pop(task, threadNumMP)) {
			tasksToComplete--;
			outputMatrixes.push(task.first * task.second, threadNumO);
		}
	}
}

void printResult(Handler<Matrix>& outputMatrixes, int threadNum)
{
	Matrix resultMatrix;
	while(outputMatrixLeft > 0) {
		if(outputMatrixes.pop(resultMatrix, threadNum)) {
			outputMatrixLeft--;
			//printMatrix(resultMatrix);
		}
	}
}


int main() {
	Handler<std::pair<Matrix, Matrix>> matrixPair(AMOUNT_PROD + AMOUNT_CONS);
	Handler<Matrix> outputMatrixes(AMOUNT_CONS + 1);

	tasksToComplete = AMOUNT_TASK * AMOUNT_PROD;
	outputMatrixLeft = AMOUNT_TASK * AMOUNT_PROD;

	std::vector<std::thread> producers;
	std::vector<std::thread> consumers;
	int i, j;

	for(i = 0; i < AMOUNT_PROD; i++) {
		producers.push_back(std::thread(producer, std::ref(matrixPair), i, AMOUNT_TASK));
	}

	for(j = 0; j < AMOUNT_CONS; j++, i++) {
		consumers.push_back(std::thread(consumer, std::ref(matrixPair), std::ref(outputMatrixes), i, j));
	}

	std::thread output(printResult, std::ref(outputMatrixes), j);

	for(i = 0; i < AMOUNT_PROD; i++) {
		producers[i].join();
	}
	for(j = 0; j < AMOUNT_CONS; j++) {
		consumers[j].join();
	}
	output.join();

	return 0;
}
