#include <stdio.h>
int index_first_negative(int fmass[], int max)
{
	int i, k=-1;
	for (i=0; i<max; i++)
		if (fmass[i] < 0)
			{
				k=i;
				break;
				
			}
	return k;
}
