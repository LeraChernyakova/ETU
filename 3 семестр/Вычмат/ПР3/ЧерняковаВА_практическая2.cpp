#include <iostream>
#include <cmath>

double delta, c;
double F(double x){
    return (1/(cos(c*x)))+1;
}

double BISECT(double Left, double Right, double Eps, int &N){
    double E = fabs(Eps)*2.0;
    double FLeft = F(Left);
    double FRight = F(Right);
    double X = (Left + Right) / 2.0;
    double Y;
    if (FLeft*FRight>0.0) {
        puts("neverno zadan interval\n");
        exit(1);
    }
    if (Eps <= 0.0) {
        puts("neverno zadana tochnost\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0)
        return Left;
    if (FRight == 0.0)
        return Right;
    while ((Right - Left) >= E) {
        X = 0.5*(Right + Left);
        Y = F(X);
        if (Y == 0.0)
            return (X);
        if (Y*FLeft < 0.0)
            Right = X;
        else {
            Left = X;
            FLeft = Y;
        }
        N++;
    };
    return(X);
}

double Round(double X, double Delta) {
    if (Delta <= 1E-9){
        puts("Неверно задана точность округления\n");
        exit(1);
    }
    if (X>0.0)
        return (Delta*(long((X / Delta) + 0.5)));
    else
        return (Delta*(long((X / Delta) - 0.5)));
}

int main(){
    setlocale(LC_ALL, "Russian");

    printf("Пункт 1:\n");
    double eps = 0.01;
    double delta = 0.01;
    int n = 0;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v", "v_max", "iter", "Conclusion");
    for(c = 3; c <=3.5 ; c += 0.1){
        double x = Round(BISECT(3, 4, eps, n), delta);
        double derivative = fabs((c*sin(c*x))/(pow(cos(c*x), 2)));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    printf("\n\nПункт 2:\n");
    c = 5;
    eps = 0.01;
    n = 0;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v", "v_max", "iter", "Conclusion");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(BISECT(3, 4, eps, n), delta);
        double derivative = fabs((c*sin(c*x))/(pow(cos(c*x), 2)));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    printf("\n\nПункт 3:\n");
    c = 3;
    delta = 0.01;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v", "v_max", "iter", "Conclusion");
    for(eps = 0.000001; eps <= 10; eps *= 10){
        double x = Round(BISECT(3, 4, eps, n), delta);
        double derivative = fabs((c*sin(c*x))/(pow(cos(c*x), 2)));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    printf("\n\nПункт 4:\n");
    c = 3;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v", "v_max", "iter", "Conclusion");
    for(eps = 0.000001, delta = 0.000001; eps <= 1 && delta <= 1; eps *= 10, delta *= 10){
        double x = Round(BISECT(3, 4, eps, n), delta);
        double derivative = fabs((c*sin(c*x))/(pow(cos(c*x), 2)));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    printf("\n\nПункт 5:\n");
    eps = 0.01;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v", "v_max", "iter", "Conclusion");
    for(c = 3; c <= 3.5; c += 0.1){
        for(delta = 0.0001; delta <= 0.1; delta *= 10){
            double x = Round(BISECT(3, 4, eps, n), delta);
            double derivative = fabs((c*sin(c*x))/(pow(cos(c*x), 2)));//вычисление абсолютного значения
            double v = 1/derivative;
            printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
            if(v < eps/delta)
                printf("%6s\n", "Good");
            else
                printf("%6s\n", "Bad");
        }
    }
    return 0;
}

