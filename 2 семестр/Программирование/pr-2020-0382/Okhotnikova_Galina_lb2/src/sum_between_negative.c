#include <stdio.h>
#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#define C 100

int sum_between_negative(int a[C], int lenght) {
	int sum = 0;
	int i1, i2, i;
	i1 = index_first_negative(a, lenght);
	i2 = index_last_negative(a, lenght);
	for (i = i1; i < i2; i++) {
		sum = sum + abs(a[i]);
	}
	return sum;


}

