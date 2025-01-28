#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

double f(double x);
double f_deriv(double x);
double f_deriv2(double x);
double spline(double x);
double s(double x);
double s_deriv(double x);
double s_deriv2(double x);
double f_sub_deriv(double (*func)(double), double x, double h);
double f_c_sub_deriv(double (*func)(double), double x, double h);
double f_sub_deriv2(double (*func)(double), double x, double h);
bool isHValid(double correct, double approx);
double M2_calculation(double (*deriv2)(double), double x0, double xn);
double delta_f_calculation(double (*f)(double), double (*f_approx) (double), double x0, double xn);

int main(){
	double x0 = 5.0000;
	double h = 0.2500;
	double correct = f_deriv(x0);
	double inaccuracy;
	double approx;
	int power = -2;
	std::printf("|%8s|%12s|%12s|%12s|%12s|\n", "x", "h", "f'(x)*", "exactf'(x)", "Inaccuracy");
	std::printf("--------------------------------------------------------------\n");
	h = std::pow(2, power);
	for (;; --power){
		approx = f_sub_deriv(f, x0, h);
		inaccuracy = std::fabs(correct - approx);
		std::printf("|%8.6g|%12.6g|%12.6g|%12.6g|%12.6g|\n", x0, h, approx, correct, inaccuracy);
		if (!isHValid(correct, approx)){
			break;
		}
	h /= 2.0;
	}
	std::printf("--------------------------------------------------------------\n\n");

	h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(5.0);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 5.0, h, correct, "-");
	approx = f_sub_deriv(f, 5.0, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 5.0, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 5.0, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 5.0, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 5.0, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 5.0, h, approx, inaccuracy);
	correct = f_deriv2(5.0);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 5.0, h, correct, "-");
	approx = f_sub_deriv2(f, 5.0, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 5.0, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");

		h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(5.25);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 5.25, h, correct, "-");
	approx = f_sub_deriv(f, 5.25, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 5.25, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 5.25, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 5.25, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 5.25, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 5.25, h, approx, inaccuracy);
	correct = f_deriv2(5.25);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 5.25, h, correct, "-");
	approx = f_sub_deriv2(f, 5.25, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 5.25, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");

		h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(5.5);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 5.5, h, correct, "-");
	approx = f_sub_deriv(f, 5.5, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 5.5, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 5.5, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 5.5, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 5.5, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 5.5, h, approx, inaccuracy);
	correct = f_deriv2(5.5);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 5.5, h, correct, "-");
	approx = f_sub_deriv2(f, 5.5, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 5.5, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");

		h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(5.75);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 5.75, h, correct, "-");
	approx = f_sub_deriv(f, 5.75, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 5.75, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 5.75, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 5.75, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 5.75, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 5.75, h, approx, inaccuracy);
	correct = f_deriv2(5.75);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 5.75, h, correct, "-");
	approx = f_sub_deriv2(f, 5.75, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 5.75, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");

		h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(6.0);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 6.0, h, correct, "-");
	approx = f_sub_deriv(f, 6.0, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 6.0, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 6.0, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 6.0, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 6.0, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 6.0, h, approx, inaccuracy);
	correct = f_deriv2(6.0);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 6.0, h, correct, "-");
	approx = f_sub_deriv2(f, 6.0, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 6.0, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");

		h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(6.25);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 6.25, h, correct, "-");
	approx = f_sub_deriv(f, 6.25, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 6.25, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 6.25, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 6.25, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 6.25, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 6.25, h, approx, inaccuracy);
	correct = f_deriv2(6.25);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 6.25, h, correct, "-");
	approx = f_sub_deriv2(f, 6.25, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 6.25, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");

		h = 0.2500;
	std::printf("|%14s|%8s|%12s|%12s|%12s|\n", "Derivative", "x", "h", "Value", "Inaccuracy");
	std::printf("----------------------------------------------------------------\n");
	correct = f_deriv(5.21);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f'(x)", 5.21, h, correct, "-");
	approx = f_sub_deriv(f, 5.21, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "right f'(x)", 5.21, h, approx, inaccuracy);
	approx = f_sub_deriv(f, 5.21, -h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "left f'(x)", 5.21, h, approx, inaccuracy);
	approx = f_c_sub_deriv(f, 5.21, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "central f'(x)", 5.21, h, approx, inaccuracy);
	correct = f_deriv2(5.21);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12s|\n", "exact f''(x)", 5.21, h, correct, "-");
	approx = f_sub_deriv2(f, 5.21, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|%12.6g|\n", "f''(x)*", 5.21, h, approx, inaccuracy);
	std::printf("----------------------------------------------------------------\n\n");


	std::printf("|%14s|%8s|%12s|%12s|\n", "Derivative", "x", "Value", "Inaccuracy");
	std::printf("---------------------------------------------------\n");
	correct = f_deriv(5.21);
	std::printf("|%14s|%8.6g|%12.6g|%12s|\n", "exact f'(x)", 5.21, correct, "-");
	approx = s_deriv(5.21);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|\n", "s'(x)", 5.21, approx, inaccuracy);
	correct = f_deriv2(5.21);
	std::printf("|%14s|%8.6g|%12.6g|%12s|\n", "exact f''(x)", 5.21, correct, "-");
	approx = s_deriv2(5.21);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|\n", "s''(x)", 5.21, approx, inaccuracy);
	approx = f_sub_deriv2(s, 5.21, h);
	inaccuracy = std::fabs(correct - approx);
	std::printf("|%14s|%8.6g|%12.6g|%12.6g|\n", "s''(x)*", 5.21, approx, inaccuracy);
	std::printf("---------------------------------------------------\n\n");

	power = -2;
	std::printf("|%8s|%12s|%12s|%12s|%12s|\n", "x", "h", "s'(x)*", "exact f'(x)", "Inaccuracy");
	std::printf("--------------------------------------------------------------\n");
	h = std::pow(2, power);
	correct = f_deriv(5.21);
	for (;; --power){
		approx = f_sub_deriv(s, 5.21, h);
		inaccuracy = std::fabs(correct - approx);
		std::printf("|%8.6g|%12.6g|%12.6g|%12.6g|%12.6g|\n", 5.21, h, approx, correct, inaccuracy);
		if (!isHValid(correct, approx)){
			break;
		}
		h /= 2.0;
	}
	std::printf("--------------------------------------------------------------\n\n");
	double h_opt = 2*std::sqrt(delta_f_calculation(f, s, 5.0, 6.25) / M2_calculation(s_deriv2, 5.0, 6.25));
	std::printf("h optimal = %g\n", h_opt);
	double nu_delta = 2 / h_opt;
	std::printf("nu delta = %g\n\n", nu_delta);
	return 0;
}

double f(double x){
	return (std::pow((2*x-3), 3)*std::pow((std::pow(x, 3)+6), 1.0/3)) / (std::pow((3*x*x-5), 1.0/4) * std::sqrt(5*x*x*x+9));
}

double f_deriv(double x){
	return (240*std::pow(x,10)-540*std::pow(x,9)-500*std::pow(x,8)+3231*std::pow(x,7)-3105*std::pow(x,6)-9558*std::pow(x,3)-6966*std::pow(x,2)+21627*x-14580)/(std::pow((3*x*x-5),5.0/4)*std::pow((x*x*x+6), 2.0/3)*std::pow((5*x*x*x+9), 3.0/2))+(30591*x*x*x*x-12501*x*x*x*x*x)/(2*std::pow((3*x*x-5), 5.0/4)*std::pow((x*x*x+6),2.0/3)*std::pow((5*x*x*x+9),3.0/2));
}

double f_deriv2(double x){
	return (3600*std::pow(x,17)-13500*std::pow(x,15)+37260*std::pow(x,14)-4335*std::pow(x,13)-303993*std::pow(x,9)+5644674*std::pow(x,7)-9065115*x*x*x*x*x+16008597*x*x*x*x-3627504*x*x*x-8667081*x*x+9666540*x-5839290)/(std::pow((3*x*x-5),9.0/4)*std::pow((x*x*x+6),5.0/3)*std::pow((5*x*x*x+9),5.0/2))+((-84015*std::pow(x,12))-283365*std::pow(x,11)-4577715*x*x*x*x*x*x)/(2*std::pow((3*x*x-5),9.0/4)*std::pow((x*x*x+6),5.0/3)*std::pow((5*x*x*x+9),5.0/2))+(2433615*std::pow(x,10)-11370861*std::pow(x,8))/(4*std::pow((3*x*x-5),9.0/4)*std::pow((x*x*x+6),5.0/3)*std::pow((5*x*x*x+9),5.0/2));
}

double f_sub_deriv(double (*func)(double), double x, double h){
	return (func(x + h) - func(x)) / h;
}

double f_c_sub_deriv(double (*func)(double), double x, double h){
	return (func(x + h) - func(x - h)) / (2*h);
}

double f_sub_deriv2(double (*func)(double), double x, double h){
	return (func(x + h) - 2*func(x) + func(x - h)) / (h * h);
}

bool isHValid(double correct, double approx){
	double inaccuracy = std::fabs(correct - approx);
	if (inaccuracy > 10)
		return false;
	return true;
}

double s(double x){
	double x0 = 5;
	while (x0 + 0.25 < x)
		x0 += 0.2500;
	double x1 = x0 + 0.2500;
	double h = x1 - x0;
	double t = (x - x0) / h;
	double f0 = f(x0), f1 = f(x1);
	double m0 = f_deriv(x0), m1 = f_deriv(x1);
	return f0*std::pow((1-t), 2)*(1+2*t) + f1*t*t*(3-2*t) + m0*h*t*std::pow((1-t), 2) - m1*t*t*h*(1-t);
}

double s_deriv(double x){
	double x0 = 5;
	while (x0 + 0.25 < x)
		x0 += 0.2500;
	double x1 = x0 + 0.2500;
	double h = x1 - x0;
	double t = (x - x0) / h;
	double f0 = f(x0), f1 = f(x1);
	double m0 = f_deriv(x0), m1 = f_deriv(x1);
	return (-6*f0*t*(1-t) + 6*f1*t*(1-t) + m0*h*(1-t)*(1-3*t) + m1*h*t*(3*t-2)) / h;
}

double s_deriv2(double x){
	double x0 = 5;
	while (x0 + 0.25 < x)
		x0 += 0.2500;
	double x1 = x0 + 0.2500;
	double h = x1 - x0;
	double t = (x - x0) / h;
	double f0 = f(x0), f1 = f(x1);
	double m0 = f_deriv(x0), m1 = f_deriv(x1);
	return 6*(f0-f1)*(2*t-1)/(h*h) + 2*(m0*(3*t-2) + m1*(3*t-1)) / h;
}

double delta_f_calculation(double (*f)(double), double (*f_approx) (double), double x0, double xn){
	double delta = 0;
	double current;
	for (double x = x0; x < xn; x += 0.01){
		current = std::fabs(f(x) - f_approx(x));
		if (current > delta)
			delta = current;
	}
	return delta;
}

double M2_calculation(double (*deriv2)(double), double x0, double xn){
	double M2 = 0;
	double current;
	for (double x = x0; x < xn; x += 0.01){
		current = std::fabs(deriv2(x));
		if (current > M2)
			M2 = current;
	}
	return M2;
}