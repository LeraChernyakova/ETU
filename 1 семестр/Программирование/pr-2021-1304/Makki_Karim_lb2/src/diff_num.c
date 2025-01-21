#include "max_num.h"
#include "min_num.h"

int diff_num(int arr[], int n){	
	int max = max_num(arr, n);
	int min = min_num(arr, n);
	int diff = max - min;
	return diff;
}
