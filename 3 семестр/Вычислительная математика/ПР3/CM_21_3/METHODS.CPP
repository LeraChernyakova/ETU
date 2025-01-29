#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include "methods.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI



double Round(double X, double Delta) {
  if (Delta <= 1E-9) {
    puts("Неверное задание точности округления\n");
    exit(1);
  }
  
  if (X > 0.0) {
    return Delta * long(X / Delta + 0.5);
  } else {
    return Delta * long(X / Delta - 0.5);
  }
}


double F(double x) {
  // функция f(x)
	extern double delta;
	double s;
	long S;

	s = pow(x, M_PI) - 1/(pow(x,4)+1);

	s = Round(s, delta);

	return s;
}

double F1(double x) {
  // функция f'(x)
	
	//double f = (M_PI * pow(x, M_PI + 7) + 2 * M_PI*pow(x, M_PI + 3) + M_PI * pow(x, M_PI - 1) + 4 * pow(x, 3)) / (pow(x, 8) + 2 * pow(x, 4) + 1);
  return x;
}

double PHI(double x) {
  // функция φ(x) - для метода простых итераций
  return x;
}

double BISECT(double Left, double Right, double Eps, int &N) {
  double E = fabs(Eps) * 2.0;
  double FLeft = F(Left);
  double FRight = F(Right);
  double X = 0.5 * (Left + Right);
  double Y;
  
  if (FLeft * FRight > 0.0) {
    puts("Неверное задание интервала\n");
    exit(1);
  }
  
  if (Eps <= 0.0) {
    puts("Неверное задание точности\n");
    exit(1);
  }
  
  if (FLeft == 0.0) {
    return Left;
  }
  
  if (FRight == 0.0) {
    return Right;
  }
  
  for (N = 0; Right - Left >= E; N++) {
    X = 0.5 * (Right + Left);	// вычисление середины отрезка
    Y = F(X);
    
    if (Y == 0.0) {
      return X;
    }
    
    if (Y * FLeft < 0.0) {
      Right = X;
    } else {
      Left = X;
      FLeft = Y;
    }
  }
  return X;
}

#ifdef __ITER
double ITER(double X0, double Eps, int &N) {
  extern double PHI(double);
  
  if (Eps <= 0.0) {
    puts("Неверное задание точности\n");
    exit(1);
  }
  
  double X1 = PHI(X0);
  double X2 = PHI(X1);
  
  for (N = 2;
       (X1 - X2) * (X1 - X2) > fabs((2 * X1 - X0 - X2) * Eps);
       N++) {
    X0 = X1;
    X1 = X2;
    X2 = PHI(X1);
  }
  
  return X2;
}
#endif

#ifdef __NEWTON
double NEWTON(double X, double Eps, int &N) {
  extern double F1(double);
  double Y, Y1, DX, Eps0;
  N = 0;
  
  double m1 = 0.0,  // наименьшее значение модуля 1-ой производной
         M2 = 0.0;  // наибольшее значение модуля 2-ой производной
  
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
  } while (fabs(DX) > Eps0);
  
  return X;
}
#endif

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
    } else {
      Left = X;
      FLeft = Y;
    }
    
    N++;
  } while (fabs(Y) >= Eps);
  
  return X;
}