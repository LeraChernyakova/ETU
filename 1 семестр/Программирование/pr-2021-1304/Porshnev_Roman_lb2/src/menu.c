#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
#include "readarr.h"

#define N 100

int main() {

	int arr[N];
	int n;
	n = readarr(arr);
	switch(arr[0]) {
            case 0:
              printf("%d\n", max(arr, n));
              break;
            case 1:
              printf("%d\n", min(arr, n));
              break;
            case 2:
              printf("%d\n", diff(arr, n)); 
              break;
            case 3:
              printf("%d\n", sum(arr, n));
              break;
            default:
              printf("Данные некорректны\n");
        }
	return 0;

}

