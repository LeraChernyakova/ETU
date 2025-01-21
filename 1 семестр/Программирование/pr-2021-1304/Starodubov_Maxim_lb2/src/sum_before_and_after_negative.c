#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int numbers[], int array_size) {
	int sum = 0;
	for (int i = 0; i < index_first_negative(numbers, array_size); i++) {
		sum += abs(numbers[i]);
	}
	for (int i = index_last_negative(numbers, array_size); i < array_size; i++) {
		sum += abs(numbers[i]);
	}
	return sum;
}
