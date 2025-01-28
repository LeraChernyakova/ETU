#include "min.h"

int min(int array[], int size) {
	if (size <= 0) {
		return 0;
	}
	int min = array[0];
	for (int i = 1; i < size; i++) {
		if (min > array[i]) {
			min = array[i];
		}
	}
	return min;
}