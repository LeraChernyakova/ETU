#include <stdio.h>
#include <stdlib.h>

int index_first_even(int A[],int n){
	int i = 0;
	while (i<n){
		if(A[i]%2 == 0){
			break;
		}else 
			i++;
	}
	return i;
}

int index_last_odd(int A[],int n){
	int i = n-1;
	while (i>=0){
		if (abs(A[i])%2 == 1){
			break;
		}else
			i--;
	}
	return i;
} 

int sum_between_even_odd(int A[],int n){
	int Begin = index_first_even(A,n);
	int End = index_last_odd(A,n);
	int summ = 0;
	for (Begin; Begin < End; Begin++){
		summ += abs(A[Begin]);
	}
	return summ;
}

int sum_before_even_and_after_odd(int A[],int n){
	int total_sum = 0;
	for(int i = 0; i < n;i++){
		total_sum += abs(A[i]);
	}
	return total_sum - sum_between_even_odd(A,n);
}

int main(){
	int arr[100];
	int arr_size = 0;
	int V; 
	scanf("%d", &V);
	char S = ' ';
	while (arr_size < 100 && S == ' '){
		scanf("%d%c",&arr[arr_size++],&S);}
	switch (V){
		case 0:
		printf("%d\n", index_first_even(arr,arr_size));
		break;
		case 1:
		printf("%d\n", index_last_odd(arr,arr_size));
		break;
		case 2:
		printf("%d\n", sum_between_even_odd(arr,arr_size));
		break;
		case 3:
		printf("%d\n", sum_before_even_and_after_odd(arr,arr_size));
		break;
		default: 
		printf("Данные некорректны\n");
		break; 
	}
	return 0;
}
