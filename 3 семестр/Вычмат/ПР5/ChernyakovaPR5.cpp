#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

double F(double x){
    return cos((M_PI*x)/2);
}

double LagrangePolynomial(double Xcoord[], double Ycoord[], double x, int n) {
    double P = 0;
    for (int i = 0; i < n; i++) {
        double L = 1;
        for (int j = 0; j < n; j++) {
            if (j != i)
                L = L * (x - Xcoord[j]) / (Xcoord[i] - Xcoord[j]);
        }
        P = P + Ycoord[i] * L;
    }

   /*std::cout<<"P(x) = ";
    for (int i = 0; i < n; i ++) {
         double r = 1;
         std::cout<<"((";
         std::cout<<Ycoord[i];
         for (int j = 0; j < n; j++) {
             if (i != j){
                std::cout<<"(x-";
                std::cout<<Xcoord[j];
                std::cout<<")";
                r *= Xcoord[i] - Xcoord[j];
             }

         }
         //std::cout << r << ' ';
         std::cout<<")/"<<r<<")";
         if (i != 5)
            std::cout<<" + ";
     } std::cout << "\n";*/

    return P;
}

int Factorial(int i) {
    double res = 1;
    for (int iter = i; iter > 1; iter--)
        res *= iter;
    return res;
}

/*void NewtonPolynomial1(double Xcoord[], double Ycoord[], double x, int n, double h) {
    double P = 0;
    double matrixY[n][n];
    double A[n];
    //arrY[2] += 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j ++) {
            if (i == 0) {
                matrixY[i][j] = Ycoord[j + 1] - Ycoord[j];
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

    std::cout << "\n";
    for (int i = 0; i < n; i++)
        std::cout<<Xcoord[i]<<" ";
    std::cout<<std::endl;

    for (int i = 0; i < n; i++)
        std::cout<<Ycoord[i]<<" ";
    std::cout<<std::endl;

     for( int i = 0; i < n; i ++){
         for (int j = 0; j < n; j++)
             std::cout << matrixY[i][j] << "\t";
         std::cout << "\n";
     }

    /*std::cout<<"P(x) = ";
    for (int i = 0; i < n; i ++) {
        if (i == 0){
              std::cout<<Ycoord[0];
             P += Ycoord[0];
        }


        else {
            double el = 1;
            double elh = 1;
            for (int k = 0; k < i; k++) {
                el *= (x - Xcoord[k]);
                elh *= h;
            }
            P += ((el * A[i - 1]) / (elh * Factorial(i)));
            std::cout << A[i - 1] / (elh * Factorial(i));
            for (int k = 0; k < i; k++) {
                std::cout<<"(x-"<<Xcoord[k]<<")";
            }
        }
        if (i != 5)
            std::cout << " + ";
    }
     std::cout << "\n";
    //return P;
}*/

void NewtonPolynomial1(double array_x[6], double array_y[6], double x, double h){
    double P = 0;
    double matrix_y[6][6] = {0};  // матрица конечных разностей
    double A[6];            // массив коэффициентов ai
    array_y[2] += 1;
    int k = 6; // Для цикла J

    //заполним матрицу конечных разностей и массив коэффициентов
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < k; j++){
            if(i == 0){
                matrix_y[i][j] = array_y[j];
            }
            else{
                matrix_y[i][j] = matrix_y[i - 1][j + 1] - matrix_y[i - 1][j];
            }
        }
        k--;
        A[i] = matrix_y[i][0] / (Factorial(i) * pow(h, i)); //вычисление коэффициента ai
    }

    std::cout << "\n";
    for (int i = 0; i < 6; i++)
        std::cout<<array_x[i]<<" ";
    std::cout<<std::endl;


     for( int i = 0; i < 6; i ++){
         for (int j = 0; j < 6; j++)
             std::cout << matrix_y[i][j] << "\t";
         std::cout << "\n";
     }

    //вычисление многочлена Ньютона
    P = A[0];
    double X[6] = {1};
    X[0] = x - array_x[0];
    for(int i = 1; i < 6; i++){
        X[i] = X[i-1]*(x - array_x[i]);
        P = P + A[i]*X[i-1];
    }
    //return P;
}


void NewtonPolynomial2(double Xcoord[], double Ycoord[], double x, int n, double h) {
    double P = 0;
    double matrixY[n][n];
    double A[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j ++) {
            if (i == 0) {
                matrixY[i][j] = Ycoord[j + 1] - Ycoord[j];
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

    std::cout << "\n";
    for (int i = 0; i < n; i++)
        std::cout<<Xcoord[i]<<" ";
    std::cout<<std::endl;

    for (int i = 0; i < n; i++)
        std::cout<<Ycoord[i]<<" ";
    std::cout<<std::endl;

     for( int i = 0; i < n; i ++){
         for (int j = 0; j < n; j++)
             std::cout << matrixY[i][j] << "\t";
         std::cout << "\n";
     }

    /*std::cout<<"P(x) = ";
    for (int i = 0; i < n; i ++) {
        if (i == 0) {
                P += Ycoord[n - 1];
                std::cout<<Ycoord[n-1];
        }
        else {
            double el = 1;
            double elh = 1;
            for (int k = n; k > (n-i); k--) {
                el *= (x - Xcoord[k-1]);
            }
            for (int k = 0; k < i; k++) elh *= h;
            P += ((el * A[i - 1]) / (elh * Factorial(i)));
            std::cout << A[i - 1] / (elh * Factorial(i));
            // std::cout << A[i - 1] / (elh * factorial(i)) << " ";
           for (int k = n; k > (n-i); k--) {
                std::cout<<"(x-"<<Xcoord[k-1]<<")";
            }
        }
        if (i != 5)
            std::cout << " + ";
    }*/
     std::cout << "\n";
    //return P;
}


double Approximation(double Xcoord[], double Ycoord[], double x, int n) {
    double a,b;
    double sumX = 0, sumY = 0, sumXY = 0, sumDX = 0;
    for (int i = 0; i < n; i ++) {
        sumX += Xcoord[i];
        sumY += Ycoord[i];
        sumXY += (Xcoord[i] * Ycoord[i]);
        sumDX += Xcoord[i] * Xcoord[i];
    }
    a = (n*sumXY - sumX * sumY) / (n * sumDX - sumX * sumX);
    b = (sumY - a * sumX) / n;
    std::cout<<"P(x) = "<<a<<"*x+"<<b<<std::endl;
    return a*x + b;
}

int main () {
    double Xcoord[6] = {0.0, 0.1, 0.4, 0.7, 1.0, 1.30};
    double Ycoord[6] = {1.0, 0.99, 0.81, 0.45, 0.0, -0.45};
    double x1 = 0.03;
    double x2 = 0.55;
    double x3 = 1.21;

    //for (int  i = 0; i < 6; i++) {
      //  Ycoord[i] = F(Xcoord[i]);
    //}
    //std::cout<<"F(x1)\n"<<F(x1)<<std::endl;
    //std::cout<<"F(x1)\n"<<F(x2)<<std::endl;
    //std::cout<<"F(x1)\n"<<F(x3)<<std::endl;


    //std::cout << "LagrangePolynomial x = 0.03\n" << LagrangePolynomial(Xcoord, Ycoord, x1, 6) << "\n";
    //std::cout << "LagrangePolynomial x = 0.55\n" << LagrangePolynomial(Xcoord, Ycoord, x2, 6) << "\n";
    //std::cout << "LagrangePolynomial x = 1.21\n" << LagrangePolynomial(Xcoord, Ycoord, x3, 6) << "\n";

    //std::cout << "NewtonPolynomial1 x = 0.03\n";
    //NewtonPolynomial1(Xcoord, Ycoord, x1, 6, 0.1);
    //std::cout << "NewtonPolynomial1 x = 0.55\n";
    //NewtonPolynomial1(Xcoord, Ycoord, x2, 0.1);
    //std::cout << "NewtonPolynomial1 x = 1.21\n";
    //NewtonPolynomial1(Xcoord, Ycoord, x3, 6, 0.1);

    //std::cout << "NewtonPolynomial2 x = 0.03\n";
    //NewtonPolynomial2(Xcoord, Ycoord, x1, 6, 0.1);
    //std::cout << "NewtonPolynomial2 x = 0.55\n";
    //NewtonPolynomial2(Xcoord, Ycoord, x2, 6, 0.1);
    //std::cout << "NewtonPolynomial2 x = 1.21\n";
    //NewtonPolynomial2(Xcoord, Ycoord, x3, 6, 0.1);

    std::cout << "Approximation x = 0.03\n" << Approximation(Xcoord, Ycoord, x1, 6)<<std::endl;
    std::cout << "Approximation x = 0.55\n" << Approximation(Xcoord, Ycoord, x2, 6)<<std::endl;
    std::cout << "Approximation x = 1.21\n" << Approximation(Xcoord, Ycoord, x3, 6)<<std::endl;

    return 0;
}
