#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"

int abs_max(int arr[], int k){
	int max = 0;
	int i;
	for(i = 0; i < k; i++){
		if(abs(max) < abs(arr[i])){
			max = arr[i];
			}
	}
	return max;
}

