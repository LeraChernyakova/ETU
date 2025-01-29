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
#define ROWS1 10
#define COLS1 5
#define ROWS2 5
#define COLS2 10
#define FILE_MATRICES "threads/matrices.txt"
#define RESULT "threads/result.txt"


void multiply(promise<MATRIX>&& prom, MATRIX& m1, MATRIX& m2) {
	MATRIX result(m1.size(), vector<int>(m2[0].size()));
	int resRows = m1.size(),
		resCols = m2[0].size(),
		newDim  = m2.size();
	for (int i = 0; i < resRows; i++) {
		for (int j = 0; j < resCols; j++) {
			for (int k = 0; k < newDim; k++) {
				result[i][j] += (m1[i][k] * m2[k][j]);
			}
		}
	}
	prom.set_value(result);

}

int main() {
	PAIR pair1(ROWS1, COLS1), pair2(ROWS2, COLS2);
	generateMatricesToFile(FILE_MATRICES, pair1, pair2);
	MATRIX matrix1(ROWS1, vector<int>(COLS1)),
						matrix2(ROWS2, vector<int>(COLS2));
	
	thread t1(readMatricesFromFile, FILE_MATRICES, ref(matrix1), ref(matrix2));
	t1.join();
  
	promise<MATRIX> resultPromise;
	future<MATRIX> resultFuture = resultPromise.get_future();
	thread t2(multiply, move(resultPromise), ref(matrix1), ref(matrix2));

	MATRIX result = resultFuture.get();
	thread t3(writeMatrixToFile, RESULT, ref(result));
	t2.join();
	t3.join();
	return 0;
}