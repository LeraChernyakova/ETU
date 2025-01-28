#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int A[],int n){
	int Begin = index_first_even(A,n);
	int End = index_last_odd(A,n);
	int summ = 0;
	for (Begin; Begin < End; Begin++){
		summ += abs(A[Begin]);
	}
	return summ;
}
