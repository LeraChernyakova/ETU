#include "sum.h"
#include "min.h"

int sum(int *arr, int n) {

	int i, x, summa;
	x = min(arr, n);
	summa = 0;
	for(i = 1; i < n; i++) {
	   if (arr[i] == x) {
              break;
           }
        summa = summa + arr[i];
	}
	return summa;

}
