#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int *array, int len){ 
	return array[max(array, len)] - array[min(array, len)]; 
}