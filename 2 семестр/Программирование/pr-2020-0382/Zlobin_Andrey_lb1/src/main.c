#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int fmass[], int max)
{
	int k=0;
	while (fmass[k]>=0)
		k++;
	return k;
}
int index_last_negative(int fmass[], int max)
{
	int k = max;
	while (fmass[k]>=0)
		k--;
	return k;
}
int sum_between_negative(int fmass[], int max)
{
	int k, start, stop, summ=0;
	start = index_first_negative(fmass, max);
	stop = index_last_negative(fmass, max);
	for (k = start; k<stop; k++)
		summ += abs(fmass[k]);
	return summ;
}
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
int main()
{
	int mass[100] = { 0 };
	int kode, i=0, result;
	scanf ("%d", &kode);
	char c = ' ';
	while (c != '\n')
	{
		scanf("%d%c", &mass[i], &c);
		i++;
	}
	switch (kode)
	{
		case 0:
			result = index_first_negative(mass, i);
			break;
		case 1:
			result = index_last_negative(mass, i);
			break;
		case 2:
			result = sum_between_negative(mass, i);
			break;
		case 3:
			result = sum_before_and_after_negative(mass, i);
			break;
		default:
		printf ("%s", "Данные некорректны");
		break;
	}
	if (kode >=0 && kode<=3)
		printf ("%d", result);
	return 0;
}
