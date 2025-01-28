#include "max.h"

int max(int array[], int size) {
	if (size <= 0) {
		return 0;
	}
	int max = array[0];
	for (int i = 1; i < size; i++) {
		if (max < array[i]) {
			max = array[i];
		}
	}
	return max;
}