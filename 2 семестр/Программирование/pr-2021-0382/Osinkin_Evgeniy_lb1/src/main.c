#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
	return *(const int *)a - *(const int *)b;
}

int main() {
	clock_t start_time, end_time;
	double bsearch_time, fullsearch_time;
	const int SIZE = 1000;
	int* array = (int*)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		scanf("%d", &array[i]);
	}
	qsort(array, SIZE, sizeof(int), cmp);
	int bsearch_number = 0;
	start_time = clock();
	int result = bsearch(&bsearch_number, array, SIZE, sizeof(int), cmp) != NULL;
	end_time = clock();
	bsearch_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	if (result) {
		printf("exists\n");
	}
	else {
		printf("doesn't exist\n");
	}
	printf("%f\n", bsearch_time);
	result = 0;
	start_time = clock();
	for (int i = 0; i < SIZE; i++) {
		if (array[i] == 0) {
			result = 1;
			break;
		}
	}
	end_time = clock();
	fullsearch_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	if (result) {
		printf("exists\n");
	}
	else {
		printf("doesn't exist\n");
	}
	printf("%f", fullsearch_time);
	free(array);
	return 0;
}