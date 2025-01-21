#include "readarr.h"

int readarr(int *arr) {

	int i, n = 0;
	char c;
	for(i = 0; i < N; i++) {
           n = n + 1;
           scanf("%d%c", &arr[i], &c); 
           if (c == '\n') {
               break;
           }
        }
	return n;
}
