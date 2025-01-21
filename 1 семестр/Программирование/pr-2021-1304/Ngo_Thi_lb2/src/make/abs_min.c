#include "min.h"

int abs_min(int arr[], int size){
	int min = abs(arr[0]);
	int result = arr[0];
	for(int i = 1; i < size; i++){
		if(min > abs(arr[i]))
		{
			min = abs(arr[i]);
			result = arr[i];
		}
	}
	return result;
}

