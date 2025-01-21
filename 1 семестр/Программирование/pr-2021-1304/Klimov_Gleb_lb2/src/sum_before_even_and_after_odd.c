#include "sum_before_even_and_after_odd.h"
int sum_before_even_and_after_odd( int arr[]){
	int N=100;
	int sum =0;
	for(int i=0;i<index_first_even(arr);i++){
		sum +=abs(arr[i]);
	}
	
	for(int i=index_last_odd(arr);i<N;i++){
		sum +=abs(arr[i]);
	}	
	
	return(sum);
}
