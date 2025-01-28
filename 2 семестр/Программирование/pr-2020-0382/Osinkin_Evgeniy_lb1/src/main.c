#include <stdio.h>

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

int diff(int array[], int size) {
	if (size <= 0) {
		return 0;
	}
	int result;
	result = max(array, size) - min(array, size);
	return result;
}

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

int main() {
	int command;
	int array[100];
	int size = 0;
	scanf("%d", &command);
	while (getchar() != '\n') {
		scanf("%d", &array[size]);
		size++;
	}
	switch (command) {
	case 0:
		printf("%d\n", max(array, size));
		break;
	case 1:
		printf("%d\n", min(array, size));
		break;
	case 2:
		printf("%d\n", diff(array, size));
		break;
	case 3:
		printf("%d\n", sum(array, size));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
	return 0;
}
