#include <stdio.h>

int max(int *array, int len){
	int res = 1;
	for(int j = 2; j < len; j++) 
		if(array[j] > array[res]) res = j;
	return res;
}
int min(int *array, int len){
	int res = 1;
	for(int j = 2; j < len; j++) 
		if(array[j] < array[res]) res = j;
	return res;
}
int diff(int *array, int len){ 
	return array[max(array, len)] - array[min(array, len)]; 
}
int sum(int *array, int len){
	int res = 0;
	for(int j = 1; j < min(array, len); j++)
		res += array[j];
	return res;
}

int main(){
	int len = 0, array[100];

	while(scanf("%d", &array[len])){
		len++;
		if(getchar() == '\n') break;
	}
	
	switch(array[0]){
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
