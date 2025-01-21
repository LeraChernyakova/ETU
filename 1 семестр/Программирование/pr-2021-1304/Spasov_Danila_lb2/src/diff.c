#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"

int diff(int arr[], int k){
	int diff;
	int mx = abs_max(arr, k);
	int mn = abs_min(arr, k);
	diff = mx - mn;	
	return diff;
}

