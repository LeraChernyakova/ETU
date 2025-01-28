#include "index_first_even.h"

int index_first_even(int A[],int n){
	int i = 0;
	while (i<n){
		if(A[i]%2 == 0){
			break;
		}else 
			i++;
	}
	return i;
}
