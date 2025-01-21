#include "index_first_negative.h"

int index_first_negative(int numbers[], int array_size) {
	for (int i = 0; i < array_size; i++) {
		if (numbers[i] < 0){
			return i;
		}
	}
}
