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

int main() {
	double eps = 0.000001, delta = 0.000001;
	int n = 0;

	// Метод Ньютона
	puts("Таблица 1\neps\t\tx\t\tn");
	for (eps = 0.000001; eps <= 0.1; eps *= 10) {
		double x = Round(NEWTON(0, eps, n), delta);
		printf("%08f\t%08f\t%d\n", eps, x, n);
	}

	eps = 0.0001;
	puts("\n\nТаблица 2\ndelta\t\tx\t\tnu\t\tnu_max");
	for (delta = 0.00001; delta <= 0.1; delta *= 10) {
		double x = Round(NEWTON(0, eps, n), delta);
		printf("%08f\t%08f\t%08f\t%08f\n", delta, x,
		nu_newton(x), eps/delta);
	}

	// Метод простых итераций
	delta = 0.000001;
	puts("\n\nТаблица 3\neps\t\tx\t\tn");
	for (eps = 0.000001; eps <= 0.1; eps *= 10) {
		double x = Round(ITER(0.5, eps, n, 0, 0.5), delta);
		printf("%08f\t%08f\t%d\n", eps, x, n);
	}

	eps = 0.0001;
	puts("\n\nТаблица 4\ndelta\t\tx\t\tnu\t\tnu_max");
	for (delta = 0.00001; delta <= 0.1; delta *= 10) {
		double x = Round(ITER(0.5, eps, n, 0, 0.5), delta);
		printf("%08f\t%08f\t%08f\t%08f\n", delta, x,
		nu_iter(x), eps/delta);
	}

	eps = 0.000001, delta = 0.000001;
	puts("\n\nТаблица 5\na\t\tb\t\tx\t\tq");
	for (double a = 0, b = 0.5; a <= 0.05; a += 0.01, b -= 0.02) {
		double x = Round(ITER(0.5, eps, n, a, b), delta);
		double min = fmin(F1(a), F1(b));
		double max = fmax(F1(a), F1(b));
		double q = fabs((min-max)/(min+max));
		printf("%08f\t%08f\t%08f\t%08f\n", a, b, x, q);
	}

	// Сравнение
	delta = 0.000001;
	puts("\n\nТаблица 6\nМетод бисекции\neps\t\tx_0\t\tx\t\tn");
	for (eps = 0.000001; eps <= 0.1; eps *= 10) {
		double x = Round(BISECT(0, 0.5, eps, n), delta);
		printf("%08f\t%08f\t%08f\t%d\n", eps, 0.f, x, n);
	}

	puts("\nМетод хорд\neps\t\tx_0\t\tx\t\tn");
	for (eps = 0.000001; eps <= 0.1; eps *= 10) {
		double x = Round(HORDA(0, 0.5, eps, n), delta);
		printf("%08f\t%08f\t%08f\t%d\n", eps, 0.f, x, n);
	}

	puts("\nМетод Ньютона\neps\t\tx_0\t\tx\t\tn");
	for (eps = 0.000001; eps <= 0.1; eps *= 10) {
		double x = Round(NEWTON(0, eps, n), delta);
		printf("%08f\t%08f\t%08f\t%d\n", eps, 0.f, x, n);
	}

	puts("\nМетод простых итераций\neps\t\tx_0\t\tx\t\tn");
	for (eps = 0.000001; eps <= 0.1; eps *= 10) {
		double x = Round(ITER(0.5, eps, n, 0, 0.5), delta);
		printf("%08f\t%08f\t%08f\t%d\n", eps, 0.5, x, n);
	}
	return 0;
}