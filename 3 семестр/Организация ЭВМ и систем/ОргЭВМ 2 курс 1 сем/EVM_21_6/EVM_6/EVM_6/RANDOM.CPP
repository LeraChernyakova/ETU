#include<stdlib.h>
#include "random.h"
/* random.c

   Copyright (c) 1995 by D.N.Kirshin, LEEI Reseach Center
   All Rights Reserved.

*/
#define RAND_A 7.74597E-1
#define RAND_M 1.37438953472E+11

static double xrand;

/* --------- Получение случайного числа, равномерное --------- */
/* --------- распределение на интервале (0,1) ---------------- */
double dnk_random(void)
 {
  xrand*=3125.0;
  xrand=xrand-((long)(xrand/RAND_M))*RAND_M;
  return xrand/RAND_M;
 }

/* ---------- Получение случайного числа, нормальное --------- */
/* ---------- распределение с математическим ожиданием M ----- */
/* ---------- и дисперсией S --------------------------------- */
double dnk_normal(double M, double S)
 {
  int i;
  double sum=0.0, xn;

  for (i=0; i < 5; i++)
   {
    xn=(2.0*dnk_random()-1.0)*RAND_A;
    sum+=xn;
   }

  return M+S*sum*(1.0+0.01*(sum*sum-3.0));
 }

/* --------- Инициализация генератора случайных чисел -------- */
void dnk_randomize(void)
 {
  char k;
  rand();
  //randomize();
  xrand=1.0*rand()/RAND_MAX;
  for (k=0; k < 10; k++)
    dnk_random();
 }