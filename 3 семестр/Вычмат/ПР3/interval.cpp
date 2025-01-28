#include <iostream>
#include <cmath>

double delta, c;
double F(double x){
    return (1/(cos(c*x)))+1;
}

double BISECT(double Left, double Right, double Eps, int &N){
    double FLeft = F(Left);
    double FRight = F(Right);
    if (FLeft*FRight>0.0)
        return 1;
    else
        return 2;
}

int main(){
    setlocale(LC_ALL, "Russian");
    double eps = 0.01;
    double delta = 0.01;
    for(c = 1; c <= 100; c += 0.5){
        if (BISECT(3, 4, eps, n) == 2)
            printf ("c - %d\n", c);
    }

    return 0;
}

