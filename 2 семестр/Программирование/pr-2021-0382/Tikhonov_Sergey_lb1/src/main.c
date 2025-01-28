#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define kol 1000


int comp(const void *a, const void *b) {
    return *(const int *) a - *(const int *) b;
}

int main() {

    clock_t start_t, end_t;
    double time_spent_on_bsearch, time_spent_on_fullsearch;
    int nums[kol];
    for (int i = 0; i < kol; ++i) {
        scanf("%d", &nums[i]);
    }

    int tagret_number = 0;

    start_t = clock();

    qsort(nums, kol, sizeof(int), comp);
    int zero_in_array = bsearch(&tagret_number, nums, kol, sizeof(int), comp) != NULL;

    end_t = clock();

    time_spent_on_bsearch = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;


    if (zero_in_array)printf("exists\n");
    else printf("doesn't exist\n");
    printf("%f\n", time_spent_on_bsearch);

    start_t = clock();

    zero_in_array = 0;
    for (int i = 0; i < kol; ++i) {
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
