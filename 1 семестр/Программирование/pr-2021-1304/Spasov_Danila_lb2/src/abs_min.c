#include <stdio.h>
#include <stdlib.h>
#include "abs_min.h"

int abs_min(int arr[], int k){
	int min = arr[0];
	int i;
	for(i = 0; i < k; i++){
		if(abs(min) > abs(arr[i])){
			min = arr[i];
			}
	}
	return min;
}

