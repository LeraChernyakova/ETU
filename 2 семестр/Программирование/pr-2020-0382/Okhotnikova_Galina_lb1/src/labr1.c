#include <stdio.h>
#include <stdlib.h>
#define C 100

int index_first_negative(int a[C], int lenght) {
	int r = -1;
	for (int i = 0; i < lenght; i++) {
		if (a[i] < 0 && r == -1) {
			r = i;
		}
	}
	return r;
}

int index_last_negative(int a[C], int lenght) {
	int i1;
	for (int i = 0; i < lenght; i++) {
		if (a[i] < 0) {
			i1 = i;
		}
	}
	return i1;
}


int sum_between_negative(int a[C], int lenght) {
	int sum = 0;
	int i1, i2, i;
	i1 = index_first_negative(a, lenght);
	i2 = index_last_negative(a, lenght);
	for (i = i1; i < i2; i++) {
		sum = sum + abs(a[i]);
	}
	printf("%d", sum);


}


int sum_before_and_after_negative(int a[C], int lenght) {
	int sum1 = 0, sum2 = 0;
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
	printf("%d", (sum1 + sum2));
}


int main()
{
	int lenght = 0;
	int a[C];
	int a_size = 0;
	char sym = ' ';
	int res1, res2, n;
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
		sum_between_negative(a, lenght);

		break;
	case 3:
		sum_before_and_after_negative(a, lenght);

		break;
	default:
		printf("Данные некорректны");
		return 0;
	}

	return 0;
}
