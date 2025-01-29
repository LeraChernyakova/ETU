#include <iostream>
#include <cstdio>
#include <cmath>

const double internet_answer = 0.633446120160759;

double f(double x){
	return cos(x + x*x*x);
}

double ROUND(double x, double delta){
	if(delta <= 0,000000001){
		puts("Неверно задана точность округления!");
		exit(1);
	}
	if(x > 0.0)
		return delta * (long((x / delta) + 0.5));
	else 
		return delta * (long((x / delta) - 0.5));
}

double RECT(double a, double b, double eps, int& n, double internet_answer, double& inaccuracy){
	n = 2;
	double h, integral, prev_integral;
	while(true){
		integral = 0;
		h = (b - a) / n;
		for (size_t i = 0; i < n; ++i)
			integral += f(a + (i + .5) * h);
		integral *= h;
		if(fabs(internet_answer - integral) < eps)
			break;
		n += 2;
	}
	prev_integral = 0;
	for(size_t i = 0; i < n / 2; ++i)
		prev_integral += f(a + (i + .5) * 2 * h);
	prev_integral *= 2*h;
	inaccuracy = fabs(integral - prev_integral) / 3.0;
	return integral;
}

double TRAP(double a, double b, double eps, int& n, double internet_answer, double& inaccuracy){
	n = 2;
	double h, integral, prev_integral;
	while(true){
		integral = 0;
		h = (b - a) / n;
		integral += (f(a) + f(b)) / 2.0;
		for(size_t i = 1; i < n; ++i)
			integral += f(a + h*i);
		integral *= h;
		if(fabs(internet_answer - integral) < eps)
			break;
		n += 2;
	}
	prev_integral = (f(a) + f(b)) / 2.0;
	for(size_t i = 1; i < n / 2; ++i)
		prev_integral += f(a + 2 * h * i);
	prev_integral *= 2*h;
	inaccuracy = fabs(integral - prev_integral) / 3.0;
	return integral;
}

double SIMPS(double a, double b, double eps, int& n, double internet_answer, double& inaccuracy){
	n = 2;
	double h, integral, prev_integral;
	while (true){
		integral = 0;
		h = (b - a) / n;
		for(size_t i = 0; i < n; ++i)
			integral += f(a + i*h) + 4*f(a + (i + .5)*h) + f(a + (i + 1)*h);
		integral *= h / 6.0;
		if(fabs(internet_answer - integral) < eps)
			break;
		n += 2;
	}
	prev_integral = 0;
	for(size_t i = 0; i < n / 2; ++i)
		prev_integral += f(a + 2*i*h) + 4*f(a + 2*(i + .5)*h) + f(a + 2*(i + 1)*h);
	prev_integral *= 2 * h / 6.0;
	inaccuracy = fabs(integral - prev_integral) / 15.0;
	return integral;
}

int main()
{
	int n;
	double a = 0.0, b = 1.0;
	double result, eps, diff_result, inac;

	eps = 0.000001;

	puts("--------------------------------------------------------------------------------------------");
	printf("     Метод\t%12s\t%10s\t%10s\t%10s\t%6s\n", "Eps", "Result", "Diff result", "Погреш", "n");
	puts("--------------------------------------------------------------------------------------------");
	printf("Прямоугольников\t       %-6f    ", eps);
	result = RECT(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Трапеций\t       %-6f    ", eps);
	result = TRAP(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Симпсона\t       %-6f    ", eps);
	result = SIMPS(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d", result, diff_result, inac, n);
	puts("\n--------------------------------------------------------------------------------------------");

	
	eps = 0.00001;

	puts("--------------------------------------------------------------------------------------------");
	printf("     Метод\t%12s\t%10s\t%10s\t%10s\t%6s\n", "Eps", "Result", "Diff result", "Погреш", "n");
	puts("--------------------------------------------------------------------------------------------");
	printf("Прямоугольников\t       %-6f    ", eps);
	result = RECT(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Трапеций\t       %-6f    ", eps);
	result = TRAP(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Симпсона\t       %-6f    ", eps);
	result = SIMPS(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d", result, diff_result, inac, n);
	puts("\n--------------------------------------------------------------------------------------------");
	

	eps = 0.0001;

	puts("--------------------------------------------------------------------------------------------");
	printf("     Метод\t%12s\t%10s\t%10s\t%10s\t%6s\n", "Eps", "Result", "Diff result", "Погреш", "n");
	puts("--------------------------------------------------------------------------------------------");
	printf("Прямоугольников\t       %-6f    ", eps);
	result = RECT(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Трапеций\t       %-6f    ", eps);
	result = TRAP(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Симпсона\t       %-6f    ", eps);
	result = SIMPS(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d", result, diff_result, inac, n);
	puts("\n--------------------------------------------------------------------------------------------");


	eps = 0.001;

	puts("--------------------------------------------------------------------------------------------");
	printf("     Метод\t%12s\t%10s\t%10s\t%10s\t%6s\n", "Eps", "Result", "Diff result", "Погреш", "n");
	puts("--------------------------------------------------------------------------------------------");
	printf("Прямоугольников\t       %-6f    ", eps);
	result = RECT(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Трапеций\t       %-6f    ", eps);
	result = TRAP(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d\n", result, diff_result, inac, n);
	printf("Симпсона\t       %-6f    ", eps);
	result = SIMPS(a, b, eps, n, internet_answer, inac);
	diff_result = fabs(internet_answer - result);
	result = ROUND(result, eps);
	printf("%8f\t  %8f     %8f%8d", result, diff_result, inac, n);
	puts("\n--------------------------------------------------------------------------------------------");
		


	return 0;
}

