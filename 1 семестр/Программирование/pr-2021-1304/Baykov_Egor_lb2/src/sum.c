#include "sum.h"
#include "min.h"

int sum(int array[], int len){
	int minimum = min(array, len);
	int total = 0;
	for(int i = 0; i < len; i++){
		if (array[i] != minimum){
			total += array[i];
		}
		else{
			break;
		}
	}
	return total;
}
