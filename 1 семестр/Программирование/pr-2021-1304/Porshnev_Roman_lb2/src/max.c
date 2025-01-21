#include "max.h"

int max(int *arr, int n) {

	int i;
	int maxinarr = arr[1];
	for(i = 1; i < n; i++) {
	   if (arr[i] >= maxinarr) {
	      maxinarr = arr[i];
	   }
	}
	return maxinarr;
}
