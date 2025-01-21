#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_between(int arr[],int n){
	int begin = index_first_zero(arr,n);
	int end = index_last_zero(arr,n);
	int sum =0;
	for (int i = begin+1;i<end;i++){
		sum+= abs(arr[i]);
	}
	return sum;
}
