#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int *arr, int n) {

	int maxinarr, mininarr,x;
	maxinarr = max(arr, n);
	mininarr = min(arr, n);
	x = maxinarr - mininarr;
	return x;

}
