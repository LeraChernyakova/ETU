#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"

int index_first_even(int arr[], int n){
	for(int i = 0;i < n;i++)
		if(arr[i] % 2 == 0)
			return i;
}
