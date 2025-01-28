#include "sum.h"
#include "min.h"

int sum(int array[], int size) {
	if (size <= 0) {
		return 0;
	}
	int minimum = min(array, size);
	int sum = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] == minimum) {
			break;
		}
		sum = sum + array[i];
	}
	return sum;
}