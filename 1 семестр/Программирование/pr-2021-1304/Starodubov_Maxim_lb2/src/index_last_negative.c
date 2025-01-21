#include "index_last_negative.h"

int index_last_negative(int numbers[], int array_size) {
	for (int i = array_size-1; i >= 0; i--) {
		if (numbers[i] < 0){
			return i;
		}
	}
}
