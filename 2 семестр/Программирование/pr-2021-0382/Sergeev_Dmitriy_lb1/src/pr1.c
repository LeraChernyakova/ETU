#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 10

int cmp(const void* a, const void* b)
{
    return (abs(*(int*)b)-abs(*(int*)a));
}

int main()
{
    int arr[N];
    int i=0;
    char c=' ';
    while (i<N && c==' ')
    {
        scanf("%d%c",&arr[i++],&c);
    }
    clock_t t=clock();
    qsort(arr,N,sizeof(int),cmp);
    clock_t t2=clock();
    float time1=((float)(t2-t))/CLOCKS_PER_SEC;
    for (int i=0;i<N;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n%f",time1);
    return 0;
}
