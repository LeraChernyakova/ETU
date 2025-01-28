#include <stdio.h>
int index_last_negative(int fmass[], int max)
{
	int k = -1, i;
	for (i=max-1; i>=0; i--)
		if (fmass[i]<0)
		{
			k=i;
			break;
		}
	return k;
}
