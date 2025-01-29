package lab3;

import java.util.Arrays;
import java.util.Random;

class Matrix {
    private final int[][] matrix;

    public Matrix(int MATRIX_SIZE) {
        matrix = new int[MATRIX_SIZE][MATRIX_SIZE];
        Random rand = new Random();
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                matrix[i][j] = -10 + rand.nextInt(20);
                System.out.println(matrix[i][j]);
            }
        }
    }

    public Matrix(int[][] matrixInput) {
        int size = matrixInput.length;
        matrix = new int[size][size];
        for (int i = 0; i < size; i++) {
            System.arraycopy(matrixInput[i], 0, matrix[i], 0, size);
        }
    }

    public Matrix multiply(Matrix matrixB) {
        int size = this.matrix.length;
        int[][] resultMatrix = new int[size][size];
        int count;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                count = 0;
                for (int k = 0; k < size; k++) {
                    count += (this.matrix[i][k] * matrixB.matrix[k][j]);
                }
                resultMatrix[i][j] = count;
            }
        }
        return new Matrix(resultMatrix);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int[] a:
             matrix) {
            sb.append(Arrays.toString(a)).append("\n");
        }

        return sb.toString();
    }
}