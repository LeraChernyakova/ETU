#include "max.h"
int abs_max(int arr[], int size){
	int result = arr[0];
	int max = abs(arr[0]);
	for(int i = 1; i < size; i++){
		if(max < abs(arr[i]))
		{
			max = abs(arr[i]);
			result = arr[i];
		}
	}
	return result;
}


		
