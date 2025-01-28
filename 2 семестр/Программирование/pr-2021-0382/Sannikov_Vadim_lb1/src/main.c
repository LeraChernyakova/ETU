#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LEN 1000

int cmp(const void * x1, const void * x2){
    return (*(int*)x1 - *(int*)x2);
}

int main(){
    int i=0, j, mas[LEN], noSwap, st;
    char sep = ' ';
    clock_t time;
    float time1, time2;

    while(i<LEN && sep == ' '){
        scanf("%d%c", &mas[i], &sep);
        i++;
    }

    time = clock();
    qsort(mas,LEN,sizeof(int),cmp);//быстрая
    time = clock() - time;

    time1 = ((float) time)/CLOCKS_PER_SEC;

    time = clock();
    for (i=LEN-1;i >= 0; i--){ //пузырьком
        noSwap=1;
        for (j=0;j < i; j++){
            if (mas[j] > mas[j+1]){
                st = mas[j];
                mas[j] = mas[j+1];
                mas[j+1] = st;
                noSwap=0;
            }
        }
        if (noSwap == 1)
            break;
    }
    time = clock() - time;

    time2 = ((float) time)/CLOCKS_PER_SEC;

    for (i=0; i < LEN; i++){
        printf("%d ", mas[i]);
    }

    printf("\n%f", time1);

    printf("\n%f", time2);

    return 0;
}
