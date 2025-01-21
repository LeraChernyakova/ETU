#include <stdio.h>

#define N 20

int index_first_negative(int array[], int length){
	int i = 0;
	while(array[i] >= 0){
		i++;
	}
	return i;
}

int index_last_negative(int array[], int length){
	int i = length - 1;
	while(array[i] >= 0){
		i--;
	}
	return i;
}

int multi_between_negative(int array[], int length){
	int multi_between = 1;
	for(int i = index_first_negative(array, length); i < index_last_negative(array, length); i++){
		multi_between *=array[i]; 
	}
	return multi_between;
}

int multi_before_and_after_negative(int array[], int length){
	int multi_before_and_after= 1;
	for(int i = 0; i < index_first_negative(array, length); i++){
		multi_before_and_after*=array[i];
	};
	for(int i = index_last_negative(array, length); i < length ; i++){
		multi_before_and_after*=array[i];
	};
	return multi_before_and_after;
}

int main(){
	int a, len, Arr[N];
	char n;

	scanf("%d\n", &a);

	for(int i = 0; i < N; i++){
		scanf("%d%c", &Arr[i], &n);
		if(n == '\n'){
			len = i + 1;
			break;
		}
	}
	switch(a){
		case(0):
			printf("%d\n", index_first_negative(Arr, len));
			break;
		case(1):
			printf("%d\n", index_last_negative(Arr, len));
			break;
		case(2):
			printf("%d\n", multi_between_negative(Arr, len));
			break;
		case(3):
			printf("%d\n", multi_before_and_after_negative(Arr, len));
			break;
		default:
			puts("Данные некорректны\n");
	}
}

