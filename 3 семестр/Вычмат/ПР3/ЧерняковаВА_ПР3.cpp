#include <iostream>
#include <cmath>

using namespace std;

double delta, eps, c = 3;

int n;

double Round_Truncation(double Y) {
   if (Y >= 0) {
   	return floor(Y);//round down
   } else {
   	return ceil(Y);//round up
   }
}

double Derivative(double x){
    return (c*sin(c*x))/(pow(cos(c*x), 2));
}

double F(double x){
    //return (1/(cos(c*x)))+1;
    return (1/(cos(c*Round_Truncation(x*1000)/1000)))+1;
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
        X = 0.5*(Right + Left), eps;
        //Y = F(X);
        Y = Round_Truncation(F(X)*1000)/1000;
        X = Round_Truncation(X*1000)/1000;
        std::cout<<X<<" "<<Y<<"\n";
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

double BISECT2(double Left, double Right, double Eps, int &N){
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
    while (N < 80) {
        X = 0.5*(Right + Left);
        Y = F(X);
        if (Y == 0.0)
            return (X);
        if (Y*FLeft < 0.0){
            Right = X;
        }

        else {
            Left = X;
            FLeft = Y;
        }
        N++;
    };
    return(X);
}

double BISECT2_1(double Left, double Right, double Eps, int &N, int v_del){
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
    //std::cout<<"N\tXn\tX*n\tdel_i\tConclusion\n";
    while (N < 80) {
        X = 0.5*(Right + Left);
        Y = F(X);
        if (Y == 0.0)
            return (X);
        if (Y*FLeft < 0.0){
            Right = X;
        }

        else {
            Left = X;
            FLeft = Y;
        }
        //std::cout<<N<<"\t"<<X<<"\t"<<Outrage2(X)<<"\t"<<fabs(X-Outrage2(X))<<"\t";
        //if (fabs(X-Outrage2(X)) <= v_del*eps)
            //std::cout<<"GOOD\n";
        //else
            //std::cout<<"BAD\n";
        N++;
    };
    return(X);
}

double HORDA(double Left, double Right, double Eps, int &N) {
    double FLeft = F(Left);
    double FRight = F(Right);
    double X, Y;
    if (FLeft * FRight > 0.0) {
        puts("Неверное задание интервала\n");
        exit(1);
    }
    if (Eps <= 0.0) {
        puts("Неверное задание точности\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0) {
        return Left;
    }
    if (FRight == 0.0) {
        return Right;
    }
    do {
        X = Left - (Right - Left) * FLeft / (FRight - FLeft);
        X = Round_Truncation(X*10000)/10000;
        //Y = F(X);
        Y = Round_Truncation(F(X)*10000)/10000;
        //std::cout<<X<<" "<<Y<<"\n";
        std::cout<<Round_Truncation(X*10000)/10000<<" "<<Y<<"\n";
        if (Y == 0.0) {
            return X;
        }
        if (Y * FLeft < 0.0) {
            Right = X;
            FRight = Y;
        }
        else {
            Left = X;
            FLeft = Y;
        }
        N++;
    } while (fabs(Y) >= Eps);
    return X;
}

double HORDA2(double Left, double Right, double Eps, int &N) {
    double FLeft = F(Left);
    double FRight = F(Right);
    double X, Y;
    if (FLeft * FRight > 0.0) {
        puts("Неверное задание интервала\n");
        exit(1);
    }
    if (Eps <= 0.0) {
        puts("Неверное задание точности\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0) {
        return Left;
    }
    if (FRight == 0.0) {
        return Right;
    }
    do {
        X = Left - (Right - Left) * FLeft / (FRight - FLeft);
        Y = F(X);
        if (Y == 0.0) {
            return X;
        }
        if (Y * FLeft < 0.0) {
            Right = X;
            FRight = Y;
        }
        else {
            Left = X;
            FLeft = Y;
        }
        //std::cout<<X<<" "<<F(X)<<"\n";
        N++;
    } while (N < 80);
    return X;
}

double HORDA2_1(double Left, double Right, double Eps, int &N, double v_del) {
    double FLeft = F(Left);
    double FRight = F(Right);
    double X, Y;
    if (FLeft * FRight > 0.0) {
        puts("Неверное задание интервала\n");
        exit(1);
    }
    if (Eps <= 0.0) {
        puts("Неверное задание точности\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0) {
        return Left;
    }
    if (FRight == 0.0) {
        return Right;
    }
    do {
        X = Left - (Right - Left) * FLeft / (FRight - FLeft);
        Y = F(X);
        if (Y == 0.0) {
            return X;
        }
        if (Y * FLeft < 0.0) {
            Right = X;
            FRight = Y;
        }
        else {
            Left = X;
            FLeft = Y;
        }
        //std::cout<<X<<"\t"<<Outrage2(X)<<"\t"<<fabs(X-Outrage2(X))<<"\t";
        //if (fabs(X-Outrage2(X)) <= v_del*eps)
            //std::cout<<"GOOD\n";
        //else
            //std::cout<<"BAD\n";
        N++;
    } while (N < 80);
    return X;
}

int main(){
    setlocale(LC_ALL, "Russian");

    /*std::cout<<"Часть 1 пункт 5\n";
    c = 3;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v_delta", "v_delta_max", "iter", "Conclusion");
    for(eps = 0.000001, delta = 0.000001; eps <= 1 && delta <= 1; eps *= 10, delta *= 10){
        double x = Round(BISECT(3, 4, eps, n), delta);
        double derivative = fabs(Derivative(x));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    std::cout<<"Часть 1 пункт 6\n";
    c = 3;
    eps = 0.1;
    n = 0;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "f(x)", "v_delta", "v_delta_max", "iter", "Conclusion");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(BISECT(3, 4, eps, n), delta);
        double derivative = fabs(Derivative(x));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, F(x), v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    //BISECT
    c = 3;
    eps = 0.01;
    n = 0;
    double X79 = BISECT2(3, 4, eps, n);

    double FX79_ = Derivative(X79);
    double v_del = 1/FX79_;

    c = 3;
    eps = 0.01;
    n = 0;
    BISECT2_1(3, 4, eps, n, v_del);*/

    c = 3;
    eps = 0.01;
    n = 0;
    BISECT(3, 4, eps, n);

    //HORDA
    /*c = 3;
    eps = 0.01;
    n = 0;
    double X79 = HORDA2(3, 4, eps, n);*/

    //double FX79_ = Derivative(X79);
    //double v_del = 1/FX79_;

    //c = 3;
    //eps = 0.01;
    //n = 0;
    //HORDA2_1(3, 4, eps, n, v_del);

    //eps = 0.01;
    //n = 0;
    //HORDA(3, 4, eps, n);

    return 0;
}

