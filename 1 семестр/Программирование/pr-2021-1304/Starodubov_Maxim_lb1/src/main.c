#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 100

int get_number(int *character_pointer){
	int cheracter;
	int result = 0;
	int result_sign = 1;
	for (cheracter = getchar(); (cheracter != ' ') && (cheracter != '\n'); cheracter = getchar()){
		if (cheracter != '-'){
			result *= 10;
			result += cheracter - '0';
		} else result_sign = -1;
	}
	*character_pointer = cheracter;
	return result*result_sign;
}

int index_first_negative(int numbers[], int array_size){
	for (int i = 0; i < array_size; i++){
		if (numbers[i] < 0){
			return i;
		}
	}
}

int index_last_negative(int numbers[], int array_size){
	for (int i = array_size-1; i >= 0; i--){
		if (numbers[i] < 0){
			return i;
		}
	}
}

int sum_between_negative(int numbers[], int array_size){
	int sum = 0;
	for (int i = index_first_negative(numbers, array_size); i < index_last_negative(numbers, array_size); i++){
		sum += abs(numbers[i]);
	}
	return sum;
}

int sum_before_and_after_negative(int numbers[], int array_size){
	int sum = 0;
	for (int i = 0; i < index_first_negative(numbers, array_size); i++){
		sum += abs(numbers[i]);
	}
	for (int i = index_last_negative(numbers, array_size); i < array_size; i++){
		sum += abs(numbers[i]);
	}
	return sum;
}

int main(){
	int cheracter;
	int *character_pointer;
	character_pointer = &cheracter;

	int function_index = get_number(character_pointer);

	int numbers[DEFAULT_SIZE];
	int array_size = 0;
	for (int i = 0; cheracter != '\n'; i++){
		numbers[i] = get_number(character_pointer);
		array_size++;
	}

	switch (function_index){
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
}
