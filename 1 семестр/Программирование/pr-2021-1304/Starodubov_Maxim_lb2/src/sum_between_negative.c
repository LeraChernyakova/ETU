#include "sum_between_negative.h"

int sum_between_negative(int numbers[], int array_size) {
	int sum = 0;
	for (int i = index_first_negative(numbers, array_size); i < index_last_negative(numbers, array_size); i++) {
		sum += abs(numbers[i]);
	}
	return sum;
}
