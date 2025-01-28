#include <iostream>
#include <cmath>

using namespace std;

double c;

double F(double x){
	return (((4*exp(2*x)+6)/(exp(4*x)+2*exp(2*x)+1))-1);
}

double nu(double x){
	return(fabs((exp(6*x)+3*exp(4*x)+3*exp(2*x)+1)/(-8*exp(4*x)-16*exp(2*x))));
}

double HORDA(double Left, double Right, double Eps, int &N){ 
	double FLeft = F(Left);
	double FRight = F(Right); 
	double X, Y;
	if(FLeft * FRight > 0.0){ 
		puts("Неверное задание интервала\n"); 
		exit(1); 
	}
	if(Eps <= 0.0){ 
		puts("Неверное задание точности\n"); 
		exit(1); 
	} 
	N = 0; 
	if(FLeft == 0.0){ 
		return Left; 
	} 
	if(FRight == 0.0){ 
		return Right; 
	} 
	do{
		X = Left - (Right - Left) * FLeft / (FRight - FLeft); 
		Y = F(X); 
		if(Y == 0.0){ 
			return X; 
		} 
		if(Y * FLeft < 0.0){ 
			Right = X; 
			FRight = Y; 
		} 
		else{ 
			Left = X; 
			FLeft = Y; 
		} 
		N++; 
	} 
	while (fabs(Y) >= Eps); 
	return X; 
}

double BISECT(double Left, double Right, double Eps, int &N){
	double E = fabs(Eps)*2.0;
	double FLeft = F(Left);
	double FRight = F(Right);
	double X = (Left + Right) / 2.0;
	double Y;

	if (FLeft*FRight>0.0){
		puts("neverno zadan interval\n");
		exit(1);
	}

	if (Eps <= 0.0){
		puts("neverno zadana tochnost\n"); exit(1);
	}

	N = 0;

	if (FLeft == 0.0)
		return Left;

	if (FRight == 0.0) 
		return Right;

	while ((Right - Left) >= E){
		X = 0.5*(Right + Left);
		Y = F(X);

		if (Y == 0.0) 
			return (X);

		if (Y*FLeft < 0.0) 
			Right = X;
		else{
			Left = X;
			FLeft = Y;
		}
		N++;
	};

	return(X);
}

double Round(double X, double Delta){
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
	double eps = 0.001;
	double delta = 0.01;
	int n = 0;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%12s\t%14s\t%16s\t%6s\t\n", "eps", "delta", "x", "nu", "nu_max", "Вывод");
	puts("-----------------------------------------------------------------------------------------------");
	for(delta = 0.1; delta >= 0.000001; delta *= 0.1){
		double x = Round(BISECT(0, 1, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%6f\t%6f\t", eps, delta, x, nu(x), eps/delta);
		if(nu(x) < eps/delta)
			printf("%6s\n", "Хорошо");
		else
			printf("%6s\n", "Плохо");
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.000001;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%13s\t%11s\n", "eps", "delta", "x", "iter");
	puts("-----------------------------------------------------------------------------------------------");
	for(eps = 0.000001; eps <= 0.1; eps *= 10){
		double x = Round(BISECT(0, 1, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%2d\n", eps, delta, x, n);
		
	}
	puts("-----------------------------------------------------------------------------------------------");
	
	eps = 0.001;
	delta = 0.000001;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%13s\t%11s\n", "left", "right", "x", "iter");
	puts("-----------------------------------------------------------------------------------------------");
	for(double i = 6, e = -0.5; i >= 1.0, e <= 0.0; i -= 1, e += 0.1){
		double x = Round(BISECT(0, i, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%2d\n", e, i, x, n);
		
	}
	puts("-----------------------------------------------------------------------------------------------");

//Метод хорд

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%12s\t%14s\t%16s\t%6s\t\n", "eps", "delta", "x", "nu", "nu_max", "Вывод");
	puts("-----------------------------------------------------------------------------------------------");
	for(delta = 0.1; delta >= 0.000001; delta *= 0.1){
		double x = Round(HORDA(0, 1, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%6f\t%6f\t", eps, delta, x, nu(x), eps/delta);
		if(nu(x) < eps/delta)
			printf("%6s\n", "Хорошо");
		else
			printf("%6s\n", "Плохо");
	}
	puts("-----------------------------------------------------------------------------------------------");

	delta = 0.0001;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%13s\t%11s\n", "eps", "delta", "x", "iter");
	puts("-----------------------------------------------------------------------------------------------");
	for(eps = 0.1; eps >= 0.000001; eps *= 0.1){
		double x = Round(HORDA(0, 1, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%2d\n", eps, delta, x, n);
		
	}
	puts("-----------------------------------------------------------------------------------------------");
	
	eps = 0.001;
	delta = 0.000001;

	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%14s\t%13s\t%11s\n", "left", "right", "x", "iter");
	puts("-----------------------------------------------------------------------------------------------");
	for(double i = 1.2; i >= 0.7; i -= 0.1){
		double x = Round(HORDA(0, i, eps, n), delta);
		printf("%6f\t%6f\t%6f\t%2d\n", 0.0, i, x, n);
		
	}
	puts("-----------------------------------------------------------------------------------------------");

//Сравнение

	delta = 0.000001;
	puts("-----------------------------------------------------------------------------------------------");
	printf("%6s\t%16s\t%8s\t%2s\t%s\t\n", "eps", "x_BISECT", "x_HORDA", "iter_B", "iter_H");
	puts("-----------------------------------------------------------------------------------------------");
	for(eps = 0.1; eps >= 0.000001; eps *= 0.1){
		int m;
		double x_b = Round(BISECT(0, 1, eps, n), delta);
		double x_h = Round(HORDA(0, 1, eps, m), delta);
		printf("%6f\t%6f\t%6f\t%3d\t%3d\n", eps, x_b, x_h, n, m);
	}
	puts("-----------------------------------------------------------------------------------------------");


	return 0;
}
