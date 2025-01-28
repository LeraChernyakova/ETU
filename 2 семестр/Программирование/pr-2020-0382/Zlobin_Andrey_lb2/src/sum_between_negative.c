#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int fmass[], int max)
{
	int k, start, stop, summ=0;
	start = index_first_negative(fmass, max);
	stop = index_last_negative(fmass, max);
	for (k = start; k<stop; k++)
		summ += abs(fmass[k]);
	return summ;
}
