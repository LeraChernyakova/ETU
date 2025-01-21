#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"

int index_last_odd(int arr[],int n){
	for(int i = n-1; i >= 0; i--)
		if(abs(arr[i] % 2) == 1)
			return i;
}
