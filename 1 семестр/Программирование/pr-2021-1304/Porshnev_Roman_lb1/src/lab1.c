#include <stdio.h>

#define N 100

int max(int *arr, int n) {

	int i;
	int maxinarr = arr[1];
	for(i = 1; i < n; i++) {
	   if (arr[i] >= maxinarr) {
	      maxinarr = arr[i];
	   }
	}
	return maxinarr;
}


int min(int *arr, int n) {

        int i;
        int mininarr = arr[1];
        for(i = 1; i < n; i++) {
           if (arr[i] <= mininarr) {
              mininarr = arr[i];
           }
	    }
	return mininarr;

}


int diff(int *arr, int n) {

	int maxinarr, mininarr,x;
	maxinarr = max(arr, n);
	mininarr = min(arr, n);
	x = maxinarr - mininarr;
	return x;

}


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
