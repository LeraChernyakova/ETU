#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 1000

int compare(const void* a, const void* b){
    int first = abs(*(int*)a);
    int second = abs(*(int*)b);
    if (first > second){
        return -1;
    } else if (first == second){
        return 0;
    } else if (first < second) {
        return 1;
    }
}

int main() {
    time_t start;
    time_t end;
    time_t answer;
    int array[LEN];
    int i;
    for (i = 0; i < LEN; i++){
        scanf("%d", &array[i]);
    }
    start = time(NULL);
    qsort(array, LEN, sizeof(int), compare);
    end = time(NULL);
    answer = end - start;
    for (i = 0; i < LEN; i++){
        if (i != LEN-1){
            printf("%d ", array[i]);
        } else {
            printf("%d\n", array[i]);
        }
    }
    printf("%d", answer);
    return 0;
}