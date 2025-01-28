#include <stdio.h>
#include "index_first_negative.h"
#define C 100

int index_first_negative(int a[C], int lenght) {
	int r = -1;
	for (int i = 0; i < lenght; i++) {
		if (a[i] < 0 && r == -1) {
			r = i;
		}
	}
	return r;
}
