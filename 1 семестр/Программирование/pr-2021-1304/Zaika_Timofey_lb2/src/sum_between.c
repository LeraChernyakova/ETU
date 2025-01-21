#include "all_funcs.h"

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

