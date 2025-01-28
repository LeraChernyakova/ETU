#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* a, const void* b)
{
    const int* k = (const int*)a;
    const int* f = (const int*)b;
    if (abs(*k)>abs(*f)){
        return -1;
    }
    if (abs(*k)<abs(*f)){
        return 1;
    }
    return 0;
}

int main()
{
    int i;
    int n=1000; 
    int a[n];
    for(i=0;i<n;i++){
        //a[i]=n-i;
        scanf("%d",&a[i]);
    }
    unsigned int start_time=clock();
    qsort(a,n,sizeof(int),cmp);
    unsigned int end_time=clock();
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("%c",'\n');
    printf("%ld",end_time-start_time);
}