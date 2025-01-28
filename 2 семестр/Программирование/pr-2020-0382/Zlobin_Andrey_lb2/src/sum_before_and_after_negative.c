#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int fmass[], int max)
{
	int k, start, stop, summ=0;
	stop = index_first_negative(fmass, max);
	start = index_last_negative(fmass, max);
	for (k = 0; k<stop; k++)
		summ += abs(fmass[k]);
	for (k=start; k<=max; k++)
		summ += abs(fmass[k]);
	return summ;
}
