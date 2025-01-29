#include <iostream>
#include <cmath>
#include <clocale>

double c;

double F(double x) {
    return c / (coshl(x)) - 0.5;
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

int main() {
    double eps = 0.01;
    double delta = 0.01;
    int n = 0;
    puts("-----------------------------------------------------------------------------------------------------------------");
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "nu", "nu_max", "iter", "Conclusion");
    puts("-----------------------------------------------------------------------------------------------------------------");
    for(c = 1; c <= 128; c *= 2){
        double x = Round(BISECT(0, 10, eps, n), delta);
        double nu = fabs(coshl(x) / (-c * tanhl(x)));
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), nu, eps/delta, n);
        if(nu < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }
    puts("-----------------------------------------------------------------------------------------------------------------");
    c = 5;
    eps = 0.01;
    puts("-----------------------------------------------------------------------------------------------------------------");
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "nu", "nu_max", "iter", "Conclusion");
    puts("-----------------------------------------------------------------------------------------------------------------");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(BISECT(0, 10, eps, n), delta);
        double nu = fabs(coshl(x) / (-c * tanhl(x)));
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), nu, eps/delta, n);
        if(nu < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }
    puts("-----------------------------------------------------------------------------------------------------------------");
    c = 20;
    delta = 0.01;
    puts("-----------------------------------------------------------------------------------------------------------------");
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "nu", "nu_max", "iter", "Conclusion");
    puts("-----------------------------------------------------------------------------------------------------------------");
    for(eps = 0.000001; eps <= 10; eps *= 10){
        double x = Round(BISECT(0, 10, eps, n), delta);
        double nu = fabs(coshl(x) / (-c * tanhl(x)));
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), nu, eps/delta, n);
        if(nu < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }
    puts("-----------------------------------------------------------------------------------------------------------------");
    c = 20;
    puts("-----------------------------------------------------------------------------------------------------------------");
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "nu", "nu_max", "iter", "Conclusion");
    puts("-----------------------------------------------------------------------------------------------------------------");
    for(eps = 0.000001, delta = 0.000001; eps <= 1 && delta <= 1; eps *= 10, delta *= 10){
        double x = Round(BISECT(0, 10, eps, n), delta);
        double nu = fabs(coshl(x) / (-c * tanhl(x)));
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), nu, eps/delta, n);
        if(nu < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }
    puts("-----------------------------------------------------------------------------------------------------------------");
    eps = 0.01;
    puts("-----------------------------------------------------------------------------------------------------------------");
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "nu", "nu_max", "iter", "Conclusion");
    puts("-----------------------------------------------------------------------------------------------------------------");
    for(c = 1; c <= 128; c *= 2){
        for(delta = 0.0001; delta <= 0.1; delta *= 10){
            double x = Round(BISECT(1, 10, eps, n), delta);
            double nu = fabs(coshl(x) / (-c * tanhl(x)));
            printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), nu, eps/delta, n);
            if(nu < eps/delta)
                printf("%6s\n", "Good");
            else
                printf("%6s\n", "Bad");
        }
    }
    puts("-----------------------------------------------------------------------------------------------------------------");
    return 0;
}
