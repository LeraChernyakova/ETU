#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_before_and_after(int arr[], int len){
	int sum=0;
	for(int i=0; i<len; i++){
		if((i >= index_first_zero(arr, len)) && (i <= index_last_zero(arr, len)))
			continue;
		sum += abs(arr[i]);
	}
	return sum;
}
