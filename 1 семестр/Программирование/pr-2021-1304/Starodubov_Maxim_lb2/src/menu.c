#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define DEFAULT_SIZE 100

int main() {
	int function_index;
	char last_character;
	scanf("%d%c", &function_index, &last_character);

	int numbers[DEFAULT_SIZE];
	int array_size = 0;

	for (int i = 0; last_character != '\n'; i++) {
		scanf("%d%c", &numbers[i], &last_character);
		array_size++;
	}

	switch (function_index) {
		case 0:
			printf("%d\n", index_first_negative(numbers, array_size));
			break;
		case 1:
			printf("%d\n", index_last_negative(numbers, array_size));
			break;
		case 2:
			printf("%d\n", sum_between_negative(numbers, array_size));
			break;
		case 3:
			printf("%d\n", sum_before_and_after_negative(numbers, array_size));
			break;
		default:
		    printf("Данные некорректны");
	}
	return 0;
}
