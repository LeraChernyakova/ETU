#include "sum.h"
#include "min.h"

int sum(int *array, int len){
	int res = 0;
	for(int j = 0; j < min(array, len); j++)
		res += array[j];
	return res;
}
