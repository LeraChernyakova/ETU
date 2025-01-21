#include <stdio.h>
#include <stdlib.h>
#define N 100

int readArr(int arr[], int len){
	char c;
	int n=0;
	while(n < len){
		scanf("%d%c", &arr[n], &c);
		n++;
		if(c == '\n')
			break;
	}
	return n;
}

int index_first_zero(int arr[], int len){
	int n=0;
	while(n < len){
		if(arr[n] == 0)
			return n;
		n++;
	}
}

int index_last_zero(int arr[], int len){
	for(int i=len-1; i>=0; i--){
		if(arr[i] == 0)
			return i;
	}
}

int sum_between(int arr[], int len, int index_first_zero, int  index_last_zero){
	int sum=0;
	for(int i=index_first_zero+1; i != index_last_zero; i++){
		sum += abs(arr[i]);
	}
	return sum;
}

int sum_before_and_after(int arr[], int len, int index_first_zero, int index_last_zero){
	int sum=0;
	for(int i=0; i<len; i++){
		if((i >= index_first_zero) && (i <= index_last_zero))
			continue;
		sum += abs(arr[i]);
	}
	return sum;
}

void user_choice(int x, int arr[], int len){
	int ifz = index_first_zero(arr, len);
	int ilz = index_last_zero(arr, len);
	switch(x){
		case 0:
			printf("%d\n", ifz);
			break;
		case 1:
			printf("%d\n", ilz);
			break;
		case 2:
			printf("%d\n", sum_between(arr, len, ifz, ilz));
			break;
		case 3:
			printf("%d\n", sum_before_and_after(arr, len, ifz, ilz));
			break;
		default:
			puts("Данные некорректны\n");
	}
}

int main(){	
	int arr[N];
	int x;
	int n;
	scanf("%d", &x);
	n = readArr(arr, N);
	user_choice(x, arr, n); 
}

