#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000  
int cmp(const void *first,const void *second)
{   int a=*((int*) first);
    int b=*((int*) second);
    if (a<b)
        return 1;
    else
        if (a>b)
            return -1;
        else
            return 0;
}
    
int main() {
    int *a=malloc(sizeof(int)*N);
    for (int i=0;i<N;i++)
        scanf("%d",&a[i]);
    time_t t1=time(NULL),t2;
    qsort(a,N,sizeof(int),cmp);
    t2=time(NULL);
    for (int i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");
    printf("%f\n",difftime(t2,t1));
}

