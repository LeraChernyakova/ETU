#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
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
