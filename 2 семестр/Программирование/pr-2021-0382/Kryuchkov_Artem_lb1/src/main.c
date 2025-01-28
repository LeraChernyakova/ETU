#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 1000


int comp(const void *a, const void *b) {
    return *(const int *) a - *(const int *) b;
}

int main() {
    // Ввод

    clock_t start_t, end_t;
    double time_spent_on_bsearch, time_spent_on_fullsearch;
    int nums[size];
    for (int i = 0; i < size; ++i) {
        scanf("%d", &nums[i]);
    }

    int tagret_number = 0;

    start_t = clock();

    qsort(nums, size, sizeof(int), comp);//sort
    int zero_in_array = bsearch(&tagret_number, nums, size, sizeof(int), comp) != NULL;

    end_t = clock();

    time_spent_on_bsearch = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;


    if (zero_in_array)printf("exists\n");
    else printf("doesn't exist\n");
    printf("%f\n", time_spent_on_bsearch);

    start_t = clock();

    zero_in_array = 0;
    for (int i = 0; i < size; ++i) {
        if (nums[i] == 0) {
            zero_in_array = 1;
        }
    }

    end_t = clock();
    time_spent_on_fullsearch = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

    if(zero_in_array)printf("exists\n");
    else printf("doesn't exist\n");

    printf("%f", time_spent_on_fullsearch);
}
