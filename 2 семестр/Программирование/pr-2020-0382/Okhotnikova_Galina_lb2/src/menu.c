#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define C 100

int main()
{
	int lenght = 0;
	int a[C];
	int a_size = 0;
	char sym = ' ';
	int res1, res2, res3, res4,  n;
	scanf("%d", &n);
	while (a_size < C && sym == ' ') {
		scanf("%d%c", &a[a_size++], &sym);
		lenght++;
	}




	switch (n) {

	case 0:
		res1 = index_first_negative(a, lenght);
		printf("%d", res1);

		break;
	case 1:
		res2 = index_last_negative(a, lenght);
		printf("%d", res2);
		break;
	case 2:
    res3 = sum_between_negative(a, lenght);
		printf("%d", res3);


		break;
	case 3:
    res4 = sum_before_and_after_negative(a, lenght);
		printf("%d", res4);

		break;
	default:
		printf("Данные некорректны");
		return 0;
	}

	return 0;
}
