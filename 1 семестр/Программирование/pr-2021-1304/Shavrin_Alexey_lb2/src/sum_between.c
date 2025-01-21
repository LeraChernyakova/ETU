#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_between(int arr[], int len){
	int sum=0;
	for(int i=index_first_zero(arr, len)+1; i != index_last_zero(arr, len); i++){
		sum += abs(arr[i]);
	}
	return sum;
}
