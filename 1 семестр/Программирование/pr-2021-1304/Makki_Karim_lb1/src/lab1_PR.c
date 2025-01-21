#include<stdio.h>

int arr_inp(int arr[]){
	char sep;
	int n = 0;
	for (int i = 0; i < 100; i++){
		scanf("%d%c", &arr[i], &sep);
		n++;
			if(sep == '\n'){
				break;
			}
	}
	return n;
}

int max_num(int arr[], int n){ 	
	int max = arr[1];
	for(int i=1;i < n;i++){
        if(arr[i]>=max){
        max = arr[i];
        }
	}
	return max; 
}

int min_num(int arr[], int n){	
	int min = arr[1];
	for(int i=1;i < n;i++){
        if(arr[i]<=min){
        min = arr[i];
        }
	}
	return min; 
}

int diff_num(int arr[], int n){	
	int max = max_num(arr, n);
	int min = min_num(arr, n);
	int diff = max - min;
	return diff;
}

int sum_num(int arr[], int n){	
	int sum = 0;
	int min = min_num(arr , n);
	for(int i = 1; i < n; i++){
		if(arr[i] == min){
			break;
		}
		sum = sum + arr[i];
	
	}
	return sum;
}


int main(){
	int arr[100];
	int n = arr_inp(arr);
	switch(arr[0]) {
            case 0:
              printf("%d\n", max_num(arr, n));
              break;
            case 1:
              printf("%d\n", min_num(arr, n));
              break;
            case 2:
              printf("%d\n", diff_num(arr, n)); 
              break;
            case 3:
              printf("%d\n", sum_num(arr, n));
              break;
            default:
              printf("Данные некорректны\n");
        }
        return 0;	
}

