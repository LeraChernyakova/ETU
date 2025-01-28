#include <iostream>
#include <cmath>


double F (double x) {
    return tan(cos(x));
}

double Lagrange (double arrX[], double arrY[], double x, int n) {
    double P = 0;
    for (int i = 0; i < n; i++) {
        double L = 1;
        for (int j = 0; j < n; j++) {
            if (j != i) L = L * (x - arrX[j]) / (arrX[i] - arrX[j]);
        }
        P = P + arrY[i] * L;
    }

    // for (int i = 0; i < n; i ++) {
    //     double r = 1;
    //     for (int j = 0; j < n; j++) {
    //         if (i != j) r *= arrX[i] - arrX[j];
    //     } std::cout << r << ' ';
    // } std::cout << "\n";

    return P;
}

int factorial (int i) {
    double res = 1;
    for (int iter = i; iter > 1; iter--) res *= iter;
    return res;
}

double Newton_1 (double arrX[], double arrY[], double x, int n, double h) {
    double P = 0;
    double matrixY[n][n], A[n];
    arrY[2] += 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j ++) {
            if (i == 0) {
                matrixY[i][j] = arrY[j + 1] - arrY[j];
                matrixY[i][j + 1] = 0;
            } else {
                if (matrixY[i - 1][j + 1] != 0) {
                    matrixY[i][j] = matrixY[i - 1][j + 1] - matrixY[i - 1][j];
                    matrixY[i][j + 1] = 0;
                } else {
                    matrixY[i][j] = 0;
                    matrixY[i][j + 1] = 0;
                }
            }
        }
        A[i] = matrixY[i][0];
    }

    // std::cout << "\n";
    // for( int i = 0; i < n; i ++){
    //     for (int j = 0; j < n; j++)
    //         std::cout << matrixY[i][j] << "\t";
    //     std::cout << "\n";
    // }

    for (int i = 0; i < n; i ++) {
        if (i == 0) P += arrY[0];
        else {
            double el = 1;
            double elh = 1;
            for (int k = 0; k < i; k++) {
                el *= (x - arrX[k]);
                elh *= h;
            }
            P += ((el * A[i - 1]) / (elh * factorial(i)));
            // std::cout << A[i - 1] / (elh * factorial(i)) << " ";
        }
    }
    // std::cout << "\n";
    return P;
}

double Newton_2 (double arrX[], double arrY[], double x, int n, double h) {
    double P = 0;
    double matrixY[n][n], A[n];

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j ++) {
            if (i == 0) {
                matrixY[i][j] = arrY[j + 1] - arrY[j];
                matrixY[i][j + 1] = 0;
            } else {
                if (matrixY[i - 1][j + 1] != 0) {
                    matrixY[i][j] = matrixY[i - 1][j + 1] - matrixY[i - 1][j];
                    matrixY[i][j + 1] = 0;
                } else {
                    matrixY[i][j] = 0;
                    matrixY[i][j+1] = 0;
                }
            }
        }
        A[i] = matrixY[i][n - 2 - i];
    }

    // std::cout << "\n";
    // for( int i = 0; i < n; i ++){
    //     for (int j = 0; j < n; j++)
    //         std::cout << matrixY[i][j] << "\t\t";
    //     std::cout << "\n";
    // }

    for (int i = 0; i < n; i ++) {
        if (i == 0) P += arrY[n - 1];
        else {
            double el = 1;
            double elh = 1;
            for (int k = n; k > (n-i); k--) {
                el *= (x - arrX[k-1]);
            }
            for (int k = 0; k < i; k++) elh *= h;
            P += ((el * A[i - 1]) / (elh * factorial(i)));
            // std::cout << A[i - 1] / (elh * factorial(i)) << " ";
        }
    }
    // std::cout << "\n";
    return P;
}

double Approximation (double arrX[], double arrY[], double x, int n) {
    double a,b;
    double sumX = 0, sumY = 0, sumXY = 0, sumDX = 0;
    for (int i = 0; i < n; i ++) {
        sumX += arrX[i];
        sumY += arrY[i];
        sumXY += (arrX[i] * arrY[i]);
        sumDX += arrX[i] * arrX[i];
    }
    a = (n*sumXY - sumX * sumY) / (n * sumDX - sumX * sumX);
    b = (sumY - a * sumX) / n;
    return a*x + b;
}

int main () {

    double arrX[6] = {5.0, 5.1, 5.2, 5.3, 5.4, 5.5}, arrY[6] = {0.29, 0.40, 0.51, 0.62, 0.74, 0.86};
    double x = 5.6; //4.9, 5.25, 5.6

    for (int  i = 0; i < 6; i++) {
        arrY[i] = F(arrX[i]);
    }

    std::cout << "F(x) = " << F(x) << '\n';
    std::cout << "Lagrange = " << Lagrange(arrX, arrY, x, 6) << "\n";
    std::cout << "Newton_1 = " << Newton_1(arrX, arrY, x, 6, 0.1) << "\n";
    std::cout << "Newton_2 = " << Newton_2(arrX, arrY, x, 6, 0.1) << "\n";
    std::cout << "Approximation = " << Approximation(arrX, arrY, x, 6);

    return 0;
}
