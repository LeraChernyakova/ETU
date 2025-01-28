#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#define C 100

int sum_before_and_after_negative(int a[C], int lenght) {
	int sum1 = 0, sum2 = 0, sum = 0;
	int i;
	int i1, i2;
	i1 = index_first_negative(a, lenght);
	i2 = index_last_negative(a, lenght);
	for (i = 0; i < i1; i++) {
		sum1 = sum1 + abs(a[i]);
	}
	for (i = i2; i < lenght; i++) {
		sum2 = sum2 + abs(a[i]);
	}
  sum = sum1 + sum2;
  return sum;
}
