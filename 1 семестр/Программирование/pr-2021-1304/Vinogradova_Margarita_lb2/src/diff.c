#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
int diff(int arr[],int N){
	int diff;
	int max = abs_max(arr,N);
	int min = abs_min(arr,N);
	diff= max-min;
	
   return diff;
	
}
