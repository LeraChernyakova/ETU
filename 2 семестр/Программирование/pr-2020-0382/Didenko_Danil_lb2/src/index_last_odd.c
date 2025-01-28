#include <stdlib.h>
#include "index_last_odd.h"

int index_last_odd(int A[],int n){
	int i = n-1;
	while (i>=0){
		if (abs(A[i])%2 == 1){
			break;
		}else
			i--;
	}
	return i;
} 
