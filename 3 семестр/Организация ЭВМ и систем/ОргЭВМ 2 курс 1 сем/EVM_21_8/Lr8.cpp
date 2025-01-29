#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

double Acos(double *xP);
/*function
Name 	Acos - compute acos
Usage 	double Acos(double *xP);
Prototype in math.h
Description Computes acos of the number pointed to by xP.
Arguments to acos must be in the range - 1 to 1, acos returns a value in the range 0 to pi.
Use the trig identities acos(x) = atan(sqrt(1 - x ^ 2) / x) */

int main()
{
	double x;
	printf("Enter x: ");
	scanf("%lf", &x);
	printf("x: \t\t%lf\n", x);
	if (x < -1 || x>1) {
		printf("Argument should be within [-1;1] range!\n");
		return 0;
	}
	printf("math.h acos(x): %lf\n", acos(x));
	printf("asm Acos(x): \t%lf\n", Acos(&x));
	return 0;
}

double Acos(double *xP)
{
	double x = *xP;
	double y = -1;
	_asm {
		fld x;		//x -> st(0);
		fld x;		//x -> st(1)
		fmul;		//x^2 -> st(0)
		fld1;		//1 -> st(0); x^2 -> st(1)
		fxch st(1);	//x^2 -> st(0); 1 -> st(1);
		fsub;		//1-x^2 -> st(0)
		fsqrt;		//sqrt(1-x^2) -> st(0)
		fld x;		//x -> st(0); sqrt(1-x^2) -> st(1)
		fdiv;		//sqrt(1-x^2) / x -> st(0)
		fld1;		//1 -> st(0); sqrt(1-x^2) / x -> st(1)
		fpatan;		//atan(st(1)/st(0)) -> st(0) == atan(sqrt(1-x^2) / x) -> st(0)
		fstp y;		//pop st(0) -> y

		fldz;		//0 -> st(0); x-> st(1)
		fld x;		//x -> st(0);
		fcom;		//cmp 0,x
		fstsw ax;	//забираем результат из сопроцессора  
		sahf		//заносим в регистр флагов
		jae c_end;	//if x >= 0
		fld y;		//y -> st(0);
		fldpi;		//pi -> st(0); y -> st(1);
		fadd;		//pi + y -> st(0)
		fstp y;		//pop st(0) -> y
	c_end:
	}
	return y;
}