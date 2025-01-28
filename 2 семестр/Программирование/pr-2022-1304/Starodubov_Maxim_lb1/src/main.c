#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int cmp(const void *a, const void *b)
{
    int first = abs(*((int *) a));
    int second = abs(*((int *) b));
    
    if (first > second)
    {
        return -1;
    } else if (second > first) 
    {
        return 1;
    }
    return 0;
}

int main()
{
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    clock_t before = clock();
    qsort(arr, SIZE, sizeof(int), cmp);
    clock_t after = clock();
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n%f", ((float)(after - before))/CLOCKS_PER_SEC);
    
    return 0;
}
