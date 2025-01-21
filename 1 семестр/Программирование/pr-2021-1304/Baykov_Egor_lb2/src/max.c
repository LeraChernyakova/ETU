#include "max.h"

int max(int array[], int len){
	int maximum = array[0];
	for (int i = 1; i < len; i++){
		if (array[i] > maximum){
			maximum = array[i];
		}
	}
	return maximum;
}
