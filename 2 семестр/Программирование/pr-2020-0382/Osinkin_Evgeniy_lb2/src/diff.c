#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int array[], int size) {
	if (size <= 0) {
		return 0;
	}
	int result;
	result = max(array, size) - min(array, size);
	return result;
}