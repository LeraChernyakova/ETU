#include <stdio.h>
#include "assets/max.h"
#include "assets/min.h"
#include "assets/diff.h"
#include "assets/sum.h"

int main(){
	int len = 0, array[100], operation;

	scanf("%d", &operation);

	while(scanf("%d", &array[len])){
		len++;
		if(getchar() == '\n') break;
	}
	
	switch(operation){
		case 0:
			printf("%d\n", array[max(array, len)]);
			break;
		case 1:
			printf("%d\n ", array[min(array, len)]);
			break;
		case 2:
			printf("%d\n ", diff(array, len));
			break;
		case 3:
			printf("%d\n ", sum(array, len));
			break;
		default:
			printf("Данные некорректны\n ");
	}
	return 0;
}
