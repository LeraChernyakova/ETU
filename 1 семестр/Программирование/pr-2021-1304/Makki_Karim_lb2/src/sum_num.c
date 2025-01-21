#include "min_num.h"

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
