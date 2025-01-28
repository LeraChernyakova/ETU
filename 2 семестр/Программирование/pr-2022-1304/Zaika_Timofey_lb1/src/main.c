#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void scanNumbers(int *array, int n){
	for(int i=0; i<n; i++){
		scanf("%d", &array[i]);
	}
}

int cmp (const void *a, const void *b){
	int *f = (int *) a;
	int *s = (int *) b;

	if (*f > *s) return 1;
	if (*f < *s) return -1;
	return 0;
}

void binarySearch(int *values, int size, int key){
	clock_t time_start = clock();
	int *pItem = (int *) bsearch(&key, values, size, sizeof(int), cmp);
	clock_t time_end = clock() - time_start;
	if (pItem == NULL){
        printf("%s\n", "doesn't exist");
    } else {
        printf("%s\n", "exists");
    }
	printf("Время бинарного поиска - %f секунд\n", (double)time_end / CLOCKS_PER_SEC);
}

void fullSearch(int *values, int size, int key){
	int foundKey = 0;
    clock_t time_start = clock();
    for(int i=0; i<size; i++){
    	if (values[i] == key){
    		foundKey = 1;
    		break;
    	}
    }
    clock_t time_end = clock() - time_start;
    if (foundKey == 0){
        printf("%s\n", "doesn't exist");
    } else {
        printf("%s\n", "exists");
    }
    printf("Время полного перебора - %f секунд\n", (double)time_end / CLOCKS_PER_SEC);
}

int main(){
	int size = 10;
	int values[size];
	scanNumbers(values, size);

	qsort(values, size, sizeof(int), cmp);

	int key = 0;
	binarySearch(values, size, key);
	fullSearch(values, size, key);
}