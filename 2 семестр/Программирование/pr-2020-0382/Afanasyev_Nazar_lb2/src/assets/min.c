#include "min.h"

int min(int *array, int len){
	int res = 0;
	for(int j = 0; j < len; j++) 
		if(array[j] < array[res]) res = j;
	return res;
}