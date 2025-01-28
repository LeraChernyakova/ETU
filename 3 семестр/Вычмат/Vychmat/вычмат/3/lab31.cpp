#include <iostream>
#include <cmath>

using namespace std;

double c;

double F(double x){
	return (((4*exp(2*x)+6)/(exp(4*x)+2*exp(2*x)+1))-1);
}

double nu(double x){
	return((exp(6*x)+3*exp(4*x)+3*exp(2*x)+1)/(-8*exp(4*x)-16*exp(2*x)));
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

int main() {
double eps = 0.001, delta = 0.1;


int n = 0;
// Метод бисекции
puts("Таблица 1\neps\t\tdelta\t\tx\t\tnu\t\tnu_max\t\tn");
for (delta = 0.000001; delta <= 0.1; delta *= 10) {
double x = Round(BISECT(0, 1, eps, n), delta);
printf("%08f\t%08f\t%08f\t%08f\t%08f\t%d\n", eps, delta,
x, nu(x), eps/delta, n);
}
delta = 0.000001;
puts("\n\nТаблица 2\neps\t\tdelta\t\tx\t\tn");
for (eps = 0.000001; eps <= 0.1; eps *= 10) {
double x = Round(BISECT(0, 1, eps, n), delta);
printf("%08f\t%08f\t%08f\t%d\n", eps, delta, x, n);
}/*
eps = 0.001; delta = 0.000001;
puts("\n\nТаблица 3\nleft\t\tright\t\tx\t\tn");
for (double i = 6; i >= 2; i--) {
double x = Round(BISECT(0, i, eps, n), delta);
printf("%08f\t%08f\t%08f\t%d\n", 1.0, i, x, n);
}
// Метод хорд
puts("\n\nТаблица 1\neps\t\tdelta\t\tx\t\tnu\t\tnu_max\t\
tn");
for (delta = 0.000001; delta <= 0.1; delta *= 10) {
double x = Round(HORDA(0, 1, eps, n), delta);
printf("%08f\t%08f\t%08f\t%08f\t%08f\t%d\n", eps, delta,
x, nu(x), eps/delta, n);
}
delta = 0.000001;
puts("\n\nТаблица 2\neps\t\tdelta\t\tx\t\tn");
for (eps = 0.000001; eps <= 0.1; eps *= 10) {


double x = Round(HORDA(0, 1, eps, n), delta);
printf("%08f\t%08f\t%08f\t%d\n", eps, delta, x, n);
}
eps = 0.01; delta = 0.000001;
puts("\n\nТаблица 3\nleft\t\tright\t\tx\t\tn");
for (double i = 0.6; i < 1.4; i += 0.1) {
double x = Round(HORDA(i, 2, eps, n), delta);
printf("%08f\t%08f\t%08f\t%d\n", i, 2.0, x, n);
}
// Сравнение
delta = 0.000001;
puts("\n\nТаблица 4\neps\t\tx_bisect\tx_chord\t\tn_bisect\
tn_chord");
for (eps = 0.000001; eps <= 0.1; eps *= 10) {
int n1;
double x_b = Round(BISECT(0, 1, eps, n), delta);
double x_c = Round(HORDA(0, 1, eps, n1), delta);
printf("%08f\t%08f\t%08f\t%d\t\t%d\n", eps, x_b, x_c, n,
n1);
}*/
return 0;
}