#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main(){
	int n = 0;
	int arr[100];
	int number;
	scanf("%d", &number);
	do{
		scanf("%d", &arr[n++]);
	}while(getchar() != '\n');
	switch(number){
		case 0:{
			printf("%d", index_first_even(arr, n));
			break;
		}
		case 1:{
			printf("%d", index_last_odd(arr, n));
			break;
		}
		case 2:{
			printf("%d", sum_between_even_odd(arr, n));
			break;
		}
		case 3:{
			printf("%d", sum_before_even_and_after_odd(arr, n));
			break;
		}
		default:{
			printf("Данные некорректны");
			break;
		}
	}
	return 0;
}
