#include "min.h"

int min(int array[], int len){
	int minimum = array[0];
	for (int i = 1; i < len; i++){
		if (array[i] < minimum){
			minimum = array[i];
		}
	}
	return minimum;
}
