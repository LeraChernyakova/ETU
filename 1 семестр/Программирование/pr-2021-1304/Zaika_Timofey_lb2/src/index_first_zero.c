#include "all_funcs.h"

int index_first_zero(int arr[], int arr_size){
	int answer_index_first_zero = -1;

	for (int i=0; i<arr_size; i++){
		if (arr[i] == 0){
			answer_index_first_zero = i;
			break;
		}
	}

	return answer_index_first_zero;
}
