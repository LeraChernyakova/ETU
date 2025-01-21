#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int array[], int len){
	return (max(array, len) - min(array, len));
}
