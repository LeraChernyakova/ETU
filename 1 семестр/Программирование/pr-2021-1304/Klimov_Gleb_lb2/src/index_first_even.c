#include "index_first_even.h"
int index_first_even(int arr[]){
	int index =0;
	int N=100;
	for(int i=0;i<N;i++){
		if (arr[i] % 2 == 0){
			index=i;
			break;
		}
	}
	return(index);
}
