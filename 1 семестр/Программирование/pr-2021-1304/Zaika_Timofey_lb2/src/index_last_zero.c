#include "all_funcs.h"

int index_last_zero(int arr[], int arr_size){
	int answer_index_last_zero = -1;
	int iter = 0;

	while(iter<arr_size){
		if (arr[iter] == 0){
			answer_index_last_zero = iter;
		}
		iter++;
	}

	return answer_index_last_zero;
	
}

