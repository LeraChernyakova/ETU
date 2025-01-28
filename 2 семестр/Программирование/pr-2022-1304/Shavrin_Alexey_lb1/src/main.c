#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000


void read_arr(int arr1[], int arr2[]){
	for (int i = 0; i < N; i++){
		scanf("%d", &arr1[i]);
		arr2[i] = arr1[i];
	}
}


void print_arr(int arr[]){
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


void bubble_sort(int arr[]){
	for (int i = N-1; i >= 0; i--){
		int no_swap = 1;
		for (int j = 0; j < i; j++){
			if (arr[j] > arr[j+1]){
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
				no_swap = 0;
			}
		}
		if (no_swap)
			break;
	}	
}


int cmp(const void *a, const void *b){
	const int *f = (const int *)a;
	const int *s = (const int *)b;
	if (*f > *s)
		return 1;
	if (*f < *s)
		return -1;
	return 0;
}


int main(){
	//init var
	int arr1[N];
	int arr2[N];
	clock_t tstart;
	clock_t tbsrt;
	clock_t tqsrt;

	//read arr
	read_arr(arr1, arr2);

	//bubble sort
	tstart = clock();
	bubble_sort(arr1);
	tbsrt = clock() - tstart;

	//quick sort
	tstart = clock();
	qsort(arr2, N, sizeof(int), cmp);
	tqsrt = clock() - tstart;

	//print ans
	print_arr(arr1);
	printf("%f\n", (float)tbsrt/CLOCKS_PER_SEC);
	printf("%f\n", (float)tqsrt/CLOCKS_PER_SEC);
	return 0;
}
