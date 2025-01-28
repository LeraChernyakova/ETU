#include <stdio.h>
#include "index_last_negative.h"
#define C 100

int index_last_negative(int a[C], int lenght) {
	int i1;
	for (int i = 0; i < lenght; i++) {
		if (a[i] < 0) {
			i1 = i;
		}
	}
	return i1;
}

