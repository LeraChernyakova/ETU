#include <iostream>
#include <cmath>

using namespace std;

double delta, eps = 0.1, c = 3;

int n;

double Round_Truncation(double Y) {
   if (Y >= 0) {
   	return floor(Y);//round down
   } else {
   	return ceil(Y);//round up
   }
}

double F(double x){
    return c / (coshl(x)) - 0.5;
    //return c / (coshl(Round_Truncation(x*1000)/1000)) - 0.5;
}

double Derivative(double x) {
	return (-c * tanhl(x)) / coshl(x);
}

double SecondDerivative(double x) {
	return (c * pow(coshl(x), 2) * pow(tanhl(x), 2) - c) / pow(coshl(x), 3);
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

double m(double a, double b, double delta){
   double mini = fabs(Derivative(a));
   for (double i = a; i <= b ;){
   	double el = fabs(Derivative(i));
   	if (el < mini){
       	mini = el;
   	}
   	i += delta;
   }
   return mini;
}

double MN(double a, double b, double delta){
   double maxi = fabs(SecondDerivative(a));
   for (double i = a; i <= b;){
   	double el = fabs(SecondDerivative(i));
   	if(el > maxi && el != INFINITY ){
       	maxi = el;
   	}
   	i += delta;
   }
   return maxi;
}

double MI(double a, double b, double delta){
   double maxi = fabs(Derivative(a));
   for (double i = a; i <= b;){
   	double el = fabs(Derivative(i));
   	if(el > maxi && el != INFINITY ){
       	maxi = el;
   	}
   	i += delta;
   }
   return maxi;
}

double NEWTON(double X, double Eps, double delta, int& N) {
    // extern double F1(double);
    double Y, Y1, DX, Eps0;
    N = 0;
    double m1 = m(2, 2.5, delta); // наименьшее значение модуля 1-ой производной
    double M2 = MN(2, 2.5, delta); // наибольшее значение модуля 2-ой производной
    Eps0 = sqrt(2 * m1 * Eps / M2);
    do {
        //Y = F(X);
        Y = Round_Truncation(F(X)*1000)/1000;
        //std::cout<<X<<" "<<Y<<"\n";
        std::cout<<Round_Truncation(X*1000)/1000<<" "<<Y<<"\n";
        if (Y == 0.0) {
            return X;
        }
        Y1 = Derivative(X);
        if (Y1 == 0.0) {
            puts("Производная обратилась в ноль\n");
            exit(1);
        }
        DX = Y / Y1;
        X -= DX;
        N++;
    } //while (N<80);
     while (fabs(DX) >= Eps0);
    return X;
}

double fi(double x,double delta){
   return x-(2/(m(2,2.5,delta)+ MI(2,2.5,delta)))* F(x);
}

double fi_(double x,double delta){
   return 1-(2/(m(2,2.5,delta)+ MI(2,2.5,delta)))* Derivative(x);
}

double PHI(double x, double a, double b, double delta) {
    if (x == 0) {
        printf("деление на 0!");
        exit(1);
    }
    double min = m(a, b, delta);
    double max = MI(a, b, delta);
    double s = x - 2 / (min + max) * (F(x));
    s = Round(s, delta);
    return(s);
}

double ITER (double X0, double Eps, int& N, double a, double b, double delta) {
    if (Eps <= 0.0) {
        puts("Неверное задание точности\n");
        exit(1);
    }
    double X1 = PHI(X0, a, b, delta);
    double X2 = PHI(X1, a, b, delta);
    for (N = 2; (X1 - X2) * (X1 - X2) > fabs((2 * X1 - X0 - X2) * Eps); N++) {
        X0 = X1;
        X1 = X2;
        X2 = PHI(X1, a, b, delta);
    }
    //std::cout<<N<<endl;
    return X2;
}

void x0(double a, double b){
    for (double i = a; i <=b; i+=0.1){
        if (F(i)*SecondDerivative(i) > 0)
            std::cout<<i<<endl;
    }
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
    std::cout<<N<<endl;
    std::cout<<X;
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
        N++;
    } while (fabs(Y) >= Eps);
    std::cout<<N<<endl;
    std::cout<<X;
    return X;
}


int main(){
    setlocale(LC_ALL, "Russian");

    //x0(2,2.5);

    //std::cout<<m(2, 2.5, 0.1)<<endl;
    //std::cout<<MN(2, 2.5, 0.1)<<endl;

    /*delta = 0.1;
    double Eps = eps;
    double m1 = m(2, 2.5, delta);
    double M2 = MN(2, 2.5, delta);
    double Eps0 = sqrt(2 * m1 * Eps / M2);
    std::cout<<Eps0<<endl;*/

    /*eps = 0.1;
    printf("c eps delta x v_delta v_delta_max iter Conclusion\n");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(NEWTON(2, eps, delta, n), delta);
        double derivative = fabs(Derivative(x));
        double v = 1/derivative;
        printf("%6f %6f %6f %6f %6lf %6f %d ", c, eps, delta, x, v, eps/delta, n);
        if(v < eps/delta)
            printf("Good\n");
        else
            printf("Bad\n");
    }*/

    //delta = 0.1;
    //NEWTON(2, eps, delta, n);

    //std::cout<<m(2, 2.5, 0.1)<<endl;
    //std::cout<<MI(2, 2.5, 0.1)<<endl;

    /*printf("c eps delta x v_delta v_delta_max iter Conclusion\n");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(ITER(2, eps, n, 2, 2.5, delta), delta);
        double derivative = fabs(1 - fi_(x, delta));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f %6f %6f %6f %6lf %6f %d ", c, eps, delta, x, v, eps/delta, n);
        if(v < eps/delta)
            printf("Good\n");
        else
            printf("Bad\n");
    }*/

    //std::cout<<ITER(2, 0.1, n, 2, 2.5, 0.1);

    //BISECT(2, 2.5, 0.1, n);

    //HORDA(2, 2.5, 0.1, n);

    return 0;
}

