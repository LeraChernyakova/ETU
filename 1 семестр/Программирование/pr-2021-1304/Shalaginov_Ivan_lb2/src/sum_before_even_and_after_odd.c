#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int arr[], int n){
	int i1 = index_first_even(arr, n);
	int i2 = index_last_odd(arr, n);
	int sum = 0;
	for(int i = 0;i < i1; i++)
		sum += abs(arr[i]);
	for(int i = i2;i < n; i++)
		sum += abs(arr[i]);
	return sum;
}
