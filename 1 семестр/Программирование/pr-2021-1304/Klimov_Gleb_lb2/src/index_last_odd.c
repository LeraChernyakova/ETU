#include "index_last_odd.h"
int index_last_odd(int arr[]){
	int N=100;
	int index =0;
	for(int i=0;i<N;i++){
		if (arr[i] % 2 != 0){
			index=i;
		}
	}
	return(index);
}

