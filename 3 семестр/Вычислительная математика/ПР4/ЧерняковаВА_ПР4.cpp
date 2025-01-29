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

double F(double x){
    //return (1/(cos(c*x)))+1;
    return (1/(cos(c*Round_Truncation(x*10)/10)))+1;
}

double Derivative(double x) {
	return (c*sin(c*x))/(pow(cos(c*x),2));
}

double SecondDerivative(double x) {
	return (2*pow(c,2)*pow(sin(c*x),2)+pow(c,2)*pow(cos(c*x),2))/(pow(cos(c*x),3));
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

double m_min(double a, double b, double delta){
   double min_ = fabs(Derivative(a));
   for (double i = a; i <= b ;){
   	double elem = fabs(Derivative(i));
   	if (elem < min_){
       	min_ = elem;
   	}
   	i += delta;
   }
   return min_;
}

double M_maxNEWTON(double a, double b, double delta){
   double max_ = fabs(SecondDerivative(a));
   for (double i = a; i <= b;){
   	double elem = fabs(SecondDerivative(i));
   	if(elem > max_ && elem != INFINITY ){
       	max_ = elem;
   	}
   	i += delta;
   }
   return max_;
}

double M_maxITER(double a, double b, double delta){
   double max_ = fabs(Derivative(a));
   for (double i = a; i <= b;){
   	double elem = fabs(Derivative(i));
   	if(elem > max_ && elem != INFINITY ){
       	max_ = elem;
   	}
   	i += delta;
   }
   return max_;
}

double NEWTON(double X, double Eps, double delta, int& N) {
    // extern double F1(double);
    double Y, Y1, DX, Eps0;
    N = 0;
    double m1 = m_min(3.5, 4, delta); // наименьшее значение модуля 1-ой производной
    double M2 = M_maxNEWTON(3.5, 4, delta); // наибольшее значение модуля 2-ой производной
    Eps0 = sqrt(2 * m1 * Eps / M2);
    do {
        //Y = F(X);
        Y = Round_Truncation(F(X)*10)/10;
        //std::cout<<X<<" "<<Y<<"\n";
        std::cout<<Round_Truncation(X*10)/10<<" "<<Y<<"\n";
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
   return x-(2/(m_min(3.5,4,delta)+ M_maxITER(3.5,4,delta)))* F(x);
}

double fi_(double x,double delta){
   return 1-(2/(m_min(3.5,4,delta)+ M_maxITER(3.5,4,delta)))* Derivative(x);
}

double PHI(double x, double a, double b, double delta) {
    if (x == 0) {
        printf("деление на 0!");
        exit(1);
    }
    double min = m_min(a, b, delta);
    double max = M_maxITER(a, b, delta);
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
    std::cout<<N<<endl;
    return X2;
}

void searchx0(double a, double b){
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

    //searchx0(3.5,4);

    //std::cout<<m_min(3.5, 4, 0.1)<<endl;
    //std::cout<<M_maxNEWTON(3.5, 4, 0.1)<<endl;

    /*delta = 0.1;
    double Eps = 0.1;
    double m1 = m_min(3.5, 4, delta);
    double M2 = M_maxNEWTON(3.5, 4, delta);
    double Eps0 = sqrt(2 * m1 * Eps / M2);
    std::cout<<Eps0<<endl;*/


    /*eps = 0.1;
    printf("%6s\t%14s\t%14s\t%14s\t%14s\t%14s\t%10s\t%10s\n", "c", "eps", "delta", "x", "v_delta", "v_delta_max", "iter", "Conclusion");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(NEWTON(4, eps, delta, n), delta);
        double derivative = fabs(Derivative(x));
        double v = 1/derivative;
        printf("%6f\t%6f\t%6f\t%6f\t%6lf\t%6f\t%d\t", c, eps, delta, x, v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }*/

    //eps = 0.1;
    //delta = 0.1;
    //NEWTON(4, eps, delta, n);

    //std::cout<<m_min(3.5, 4, 0.1)<<endl;
    //std::cout<<M_maxITER(3.5, 4, 0.1)<<endl;

    eps = 0.1;
    printf("%6s %14s %14s %14s %14s %14s %10s %10s\n", "c", "eps", "delta", "x", "v_delta", "v_delta_max", "iter", "Conclusion");
    for(delta = 0.00001; delta <= 0.1; delta *= 10){
        double x = Round(ITER(4, eps, n, 3.5, 4, delta), delta);
        double derivative = fabs(1 - fi_(x, delta));//вычисление абсолютного значения
        double v = 1/derivative;
        printf("%6f %6f %6f %6f %6lf %6f %d ", c, eps, delta, x, v, eps/delta, n);
        if(v < eps/delta)
            printf("%6s\n", "Good");
        else
            printf("%6s\n", "Bad");
    }

    //std::cout<<ITER(4, 0.1, n, 3.5, 4, 0.1);

    //BISECT(3.5, 4, 0.1, n);

    //HORDA(3.5, 4, 0.1, n);

    return 0;
}

