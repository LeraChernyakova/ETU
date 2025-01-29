#include "task2.h"
#define ROWS1 10
#define COLS1 5
#define ROWS2 5
#define COLS2 10
#define MOD 200
#define FILENAME "matrices.txt"
#define OUTPUT_FILE "result2.txt"


int main() {
	PAIR_INT dim1(ROWS1, COLS1), dim2(ROWS2, COLS2);
	generateTxtFile(FILENAME, dim1, dim2);
	MATRIX matrix1(ROWS1, vector<int>(COLS1)),
						matrix2(ROWS2, vector<int>(COLS2));
	
	thread t1(readMatricesFromFile, FILENAME, ref(matrix1), ref(matrix2));
	t1.join();

	promise<MATRIX> matrixMultPromise;
	future<MATRIX> matrixMultFuture = matrixMultPromise.get_future();
	thread t2(matrixMult, move(matrixMultPromise), ref(matrix1), ref(matrix2));

	MATRIX result = matrixMultFuture.get();
	thread t3(printMatrixToFile, OUTPUT_FILE, ref(result));

	t2.join();
	t3.join();
	return 0;
}





void matrixMult(promise<MATRIX>&& prom, MATRIX& m1, MATRIX& m2) {
	MATRIX result(m1.size(), vector<int>(m2[0].size()));
	int oldRows = m1.size(),
		oldCols = m2[0].size(),
		newDim  = m2.size();
	for (int i = 0; i < oldRows; i++) {
		for (int j = 0; j < oldCols; j++) {
			for (int k = 0; k < newDim; k++) {
				// cout << i << ' ' << j << ' ' << k << '\n';
				result[i][j] += (m1[i][k] * m2[k][j]);
			}
		}
	}
	prom.set_value(result);

}