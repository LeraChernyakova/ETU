#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int compare(int* a,int* b){
    return abs(*a)<=abs(*b);
}

int main() {
    int digit[N];
    for (int i = 0;i<N;i++){
        scanf("%d",&digit[i]);
    }
    int t = clock();
    qsort(&digit[0],N,sizeof(int),(int (*)(const void*,const void*))compare);
    int t2 = clock();
    for(int j = 0;j<N;j++){
        printf("%d ",digit[j]);
    }
    printf("\n%d",t2-t);
    return 0;
}

