#include <stdio.h>
#include <stdlib.h>


int index_first_zero(int arr[], int arr_size){
	int answer_index_first_zero = 0;

	for (int i=0; i<arr_size; i++){
		if (arr[i] == 0){
			answer_index_first_zero = i;
			break;
		}
	}

	return answer_index_first_zero;
}

int index_last_zero(int arr[], int arr_size){
	int answer_index_last_zero = 0;
	int iter = 0;

	while(iter<arr_size){
		if (arr[iter] == 0){
			answer_index_last_zero = iter;
		}
		iter++;
	}

	return answer_index_last_zero;
	
}

int sum_between(int arr[], int arr_size){
	int answer_sum_between = 0;

	int index_start_zero = index_first_zero(arr, arr_size);
	int index_finish_zero = index_last_zero(arr, arr_size);

	int module_num = 0;

	for (int i = index_start_zero; i<index_finish_zero; i++) {
		module_num = abs(arr[i]);
		answer_sum_between += module_num;
	}

	return answer_sum_between;
}

int sum_before_after(int arr[], int arr_size){
	int answer_sum_before_after = 0;
	int iter = 0;

	int index_start_zero = index_first_zero(arr, arr_size);
	int index_finish_zero = index_last_zero(arr, arr_size);

	int module_num = 0;

	while (iter<index_start_zero){
		module_num = abs(arr[iter]);
		answer_sum_before_after += module_num;
		iter++;
	}

	while(index_finish_zero<arr_size){
		module_num = abs(arr[index_finish_zero]);
		answer_sum_before_after += module_num;
		index_finish_zero++;
	}

	return answer_sum_before_after;
}


int main(){
	int task_number = 0;

	scanf("%d", &task_number);
	
	if (task_number < 0 || task_number > 3) { 
		printf("Данные некорректны\n");
	} else { 
		int arr_size = 100;
        	int arr[arr_size];
        	char stop_char;

		int iter_num = 0;

		while (iter_num < arr_size) {
			scanf("%d%c", &arr[iter_num], &stop_char);
			iter_num++;
			if (stop_char == '\n'){
				break;
			}
		}

		arr_size = iter_num;

		int task_answer = 0;

		switch (task_number) {
			case 0:
				task_answer = index_first_zero(arr, arr_size);
				printf("%d\n", task_answer);
				break;
			case 1:
				task_answer = index_last_zero(arr, arr_size);
				printf("%d\n", task_answer);
				break;
			case 2:
				task_answer = sum_between(arr, arr_size);
				printf("%d\n", task_answer);
				break;
			case 3:
				task_answer = sum_before_after(arr, arr_size);
				printf("%d\n", task_answer);
				break;
		}
	}

	return 0;
}
