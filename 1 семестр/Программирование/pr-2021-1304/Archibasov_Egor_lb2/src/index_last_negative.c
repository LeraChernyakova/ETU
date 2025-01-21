#include "index_last_negative.h"

int index_last_negative(int array[], int length){
	int i = length - 1;
       	while(array[i] >= 0){
		i--;
	};
	return i;
}
