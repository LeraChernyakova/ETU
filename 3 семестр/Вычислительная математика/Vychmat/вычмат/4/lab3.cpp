#include <cstdio>
#include <cmath>

using namespace std;

double F(double x) {
	return x*x + 5.0*sin(x);
}

double F1(double x) {
	return 2*x + 5*cos(x);
}

double F2(double x) {
	return 2 - 5*sin(x);
}

double nu_newton(double x){
	return pow(F1(x), 2)/(pow(F1(x), 2) - F(x)*F2(x)); 
}

double nu_iter(double x){
	return fabs(-11.03108758/(2*F1(x))); 
}

double NEWTON(double X, double Eps, int& N) {
	double Y, Y1, DX, Eps0;
	N = 0;
	double m1 = 4.359; // наименьшее значение модуля 1-ой производной
	double M2 = 6.924; // наибольшее значение модуля 2-ой производной
	Eps0 = sqrt(2 * m1 * Eps / M2);
	do {
		Y = F(X);
		if (Y == 0.0) {
			return X;
		}
		Y1 = F1(X);
		if (Y1 == 0.0) {
			puts("Производная обратилась в ноль\n");
			exit(1);
		}
		DX = Y / Y1;
		X -= DX;
		N++;
	} while (fabs(DX) >= Eps0);
	return X;
}

double PHI(double x, double a, double b) {
	if (x == 0) {
		printf("деление на 0!");
		exit(1);
	}
	double min = fmin(F1(a), F1(b));
	double max = fmax(F1(a), F1(b));
	double s = x - 2 / (min + max) * (F(x));
	return(s);
}

double ITER (double X0, double Eps, int& N, double a, double b) {
	if (Eps <= 0.0) {
		puts("Неверное задание точности\n");
		exit(1);
	}
	double X1 = PHI(X0, a, b);
	double X2 = PHI(X1, a, b);
	for (N = 2; pow((X1 - X2), 2) > fabs((2 * X1 - X0 - X2) * Eps); N++) {
		X0 = X1;
		X1 = X2;
		X2 = PHI(X1, a, b);
	}
	return X2;
}

double BISECT(double Left, double Right, double Eps, int& N) {
	double E = fabs(Eps)*2.0;
	double FLeft = F(Left);
	double FRight = F(Right);
	double X = (Left + Right) / 2.0;
	double Y;
	if (FLeft * FRight > 0.0) {
		puts("Неверное задание интервала\n");
		exit(1);
	}
	if (Eps <= 0.0) {
		puts("Неверное задание точности\n");
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
			return X;
		if (Y*FLeft < 0.0)
			Right = X;
		else {
			Left = X;
			FLeft = Y;
		}
		N++;
	}
	return X;
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
	if (FLeft == 0.0) { return Left; }
	if (FRight == 0.0) { return Right; }
	do {
		X = Left - (Right - Left) * FLeft / (FRight - FLeft);
		Y = F(X);
		if (Y == 0.0) { return X; }
		if (Y * FLeft < 0.0) { Right = X; FRight = Y; }
		else { Left = X; FLeft = Y; }
		N++;
	} while (fabs(Y) >= Eps);
	return X;
}

double Round(double X, double Delta) {
	if (Delta <= 1E-9) {
		puts("Неверно задана точность округления\n");
		exit(1);
	}
	if (X>0.0)
		return (Delta*(long((X / Delta) + 0.5)));
	else
		return (Delta*(long((X / Delta) - 0.5)));
}

int main(){

	double eps = 0.000001;
	double delta = 0.000001;
	int n = 0;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%13s\t%12s\n", "eps", "eps2", "x", "iter");
	puts("-----------------------------------------------------------------------------------------------");
	for(eps = 0.000001; eps <= 0.1; eps *= 10){
		double x = Round(NEWTON(-2.443, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%2d\t\n", eps, sqrt(2*4.359*eps/6.924), x, n);
	}
	puts("-----------------------------------------------------------------------------------------------");

	eps = 0.001;
	n = 0;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%13s\t%12s\t%16s\t%10s\n", "eps", "delta", "x", "nu", "nu_max", "Вывод");
	puts("-----------------------------------------------------------------------------------------------");
	for(delta = 0.000001; delta <= 0.01; delta *= 10){
		double x = Round(NEWTON(-2.443, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%6f\t%6f\t%6s\n", eps, delta, x, nu_newton(x), eps/delta, nu_newton(x) < eps/delta ? "Хорошо" : "Плохо");
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.000001;
	n = 0;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%9s\n", "eps", "x", "n");
	puts("-----------------------------------------------------------------------------------------------");
	for(eps = 0.000001; eps <= 0.1; eps *= 10){
		double x = Round(ITER(-2.443, eps, n, -2.443, -1.745), delta);
		printf("%6f\t%6f\t%d\n", eps, x, n);
	}
	puts("-----------------------------------------------------------------------------------------------");

	eps = 0.001; 
	n = 0;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%14s\t%13s\t%16s\t%10s\n", "eps", "delta", "x", "nu", "nu_max", "Вывод");
	puts("-----------------------------------------------------------------------------------------------");
	for(delta = 0.000001; delta <= 0.01; delta *= 10){
		double x = Round(ITER(-2.443, eps, n, -2.443, -1.745), delta);
		printf("%6f\t%6f\t%6f\t%6f\t%6f\t%s\n", eps, delta, x, nu_iter(x), eps/delta, nu_iter(x) < eps/delta ? "Хорошо" : "Плохо");
	}
	puts("-----------------------------------------------------------------------------------------------");

	eps = 0.000001;
	delta = 0.000001;
	n = 0;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%14s\t%13s\n", "left", "right", "x", "q");
	puts("-----------------------------------------------------------------------------------------------");
	for(double left = -2.443, right = -1.745; left <= -2.143, right >= -2.045; left += 0.05, right -= 0.05){
		double x = Round(ITER(-2.443, eps, n, left, right), delta);
		printf("%6f\t%6f\t%6f\t%6f\n", left, right, x, fabs((fmin(F1(left), F1(right))-fmax(F1(left), F1(right)))/(fmin(F1(left), F1(right))+fmax(F1(left), F1(right)))));
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.000001;
	n = 0;
	int i = 1;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%14s\t%13s\t%11s\n", "Метод", "eps", "x_0", "x", "iter");
	puts("-----------------------------------------------------------------------------------------------");
	for(eps = 0.000001, i = 1; eps <= 0.1; eps *= 10, i++){
		double x = Round(BISECT(-2.443, -1.745, eps, n), delta);
		if(i == 1)
			printf("Бисекции\t");
		else
			printf("\t\t");
		printf("%6f\t%6f\t%6f\t%2d\n", eps, -2.443, x, n);
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.000001;
	n = 0;
	i = 1;

	for(eps = 0.000001, i = 1; eps <= 0.1; eps *= 10, i++){
		double x = Round(HORDA(-2.443, -1.745, eps, n), delta);
		if(i == 1)
			printf("Хорд\t\t");
		else
			printf("\t\t");
		printf("%6f\t%6f\t%6f\t%2d\n", eps, -2.443, x, n);
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.000001;
	n = 0;
	i = 1;

	for(eps = 0.000001, i = 1; eps <= 0.1; eps *= 10, i++){
		double x = Round(NEWTON(-2.433, eps, n), delta);
		if(i == 1)
			printf("Ньютона\t\t");
		else
			printf("\t\t");
		printf("%6f\t%6f\t%6f\t%2d\n", eps, -2.443, x, n);
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.000001;
	n = 0;
	i = 1;

	for(eps = 0.000001, i = 1; eps <= 0.1; eps *= 10, i++){
		double x = Round(ITER(-2.443, eps, n, -2.443, -1.745), delta);
		if(i == 1 && i != 2)
			printf("Простых");
		if(i != 1 && i == 2)
			printf("итераций\t");
		else
			printf("\t\t");
		printf("%6f\t%6f\t%6f\t%2d\n", eps, -2.443, x, n);
	}
	puts("-----------------------------------------------------------------------------------------------");

	return 0;
}
