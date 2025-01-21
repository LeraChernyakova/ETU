#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_before_and_after(int arr[],int n){
	int begin = index_first_zero(arr,n);
	int end = index_last_zero(arr,n);
	int sum =0;
	for (int i = 0;i<begin;i++){
		sum+= abs(arr[i]);
	}
	for (int i =end+1;i<n;i++){
		sum+= abs(arr[i]);
	}
	return sum;
	}
