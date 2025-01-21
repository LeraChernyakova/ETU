include "sum_between_even_odd.h"
int sum_between_even_odd(int arr[]){
	int N=100;
	int sum =0;
	for(int i=index_first_even(arr);i<index_last_odd(arr);i++){
		sum +=abs(arr[i]);
	}
	return(sum);
}
