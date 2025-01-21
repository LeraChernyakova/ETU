#include <stdio.h>
#include <stdlib.h>
#define N 100
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
int main()
	{
	int numb_les;
	/*printf("Введите номер задания и заполните массив");*/
	scanf("%d ",&numb_les);
	int arr[N];
	int n=0;
	char c;
	while (n<N){
		scanf("%d%c",&arr[n],&c);
		n++;
		if (c == '\n'){
		break;}
	}

	switch (numb_les){
	case 0: {printf("%d\n",index_first_zero(arr,n));
		break;}
	case 1:{printf("%d\n",index_last_zero(arr,n));
		break;}
	case 2: {printf("%d\n",sum_between(arr,n));
		break;}
	case 3: {printf("%d\n",sum_before_and_after(arr,n));
		break;}
	default: printf("Данные некорректны\n");
	}	

	return 0;
	}
