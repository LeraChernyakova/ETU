#include "all_funcs.h"


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
