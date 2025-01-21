#include "all_funcs.h"

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

