#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define N 1000

int cmp(const void* arg1, const void* arg2){
	int x1 = *(int*)arg1;
	int x2 = *(int*)arg2;
	
	if (x1 == INT_MIN && x2 != INT_MIN) return -1;
	if (x1 == INT_MIN && x2 == INT_MIN) return 0;
	if (x1 != INT_MIN && x2 == INT_MIN) return 1;
	else return abs(x2) - abs(x1);
}

int main(){
	int arr[N];
	clock_t clocks;
	
	for (int i = 0; i < N; i++)
		scanf("%d", arr+i);
	
	clocks = clock();
	qsort(arr, N, sizeof(int), cmp);
	clocks = clock() - clocks;
	
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n%f\n", (double)clocks/CLOCKS_PER_SEC);
	
	return 0;
}
