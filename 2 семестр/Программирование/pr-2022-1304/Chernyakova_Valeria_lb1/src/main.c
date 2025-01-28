#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int arr[1000], cnt_zero = 0, key = 0;
    clock_t t1, t2;
    for (int i = 0; i < 1000; i++)
        scanf ("%d", &arr[i]);
    qsort(arr, 1000, sizeof(int), cmp);
    t1 = clock();
    int *result = (int*) bsearch(&key, arr, 1000, sizeof(int), cmp);
    t1 = clock() - t1;
    if (result)
        printf("exists\n");
    else
        printf ("doesn't exist\n");
    printf ("%ld\n",t1);
    t2 = clock();
    for (int i = 0; i < 1000; i++)
        if (arr[i] == 0)
            cnt_zero++;
    t2 = clock()-t2;
    if (cnt_zero != 0)
        printf("exists\n");
    else
        printf ("doesn't exist\n");
    printf ("%ld",t2);
    return 0;
}