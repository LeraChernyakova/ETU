#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int compare(const void * x1, const void * x2)   
{
  return ( *(int*)x1 - *(int*)x2 );
}

int main() {
    double time_s1, time_e1, time_s2, time_e2, help;
    int list [1000] = {0};
    for(int i = 0; i < 1000; i++){
        scanf("%d", &list[i]);
    }
    time_s1 = clock();
    for(int i = 0; i < 999; i++){
        for(int j = i; i < 1000; i++){
            if (list[i] > list[j]){
                int a = list[i];
                list[i] = list[j];
                list[j] = a;
            }
        }
    }
    time_e1 = (clock() - time_s1)/CLOCKS_PER_SEC;
    time_s2 = clock();
    qsort(list, 1000, sizeof(int), compare);
    time_e2 = (clock() - time_s2)/CLOCKS_PER_SEC;
    for(int i = 0; i<1000; i++){
        printf("%d ", list[i]);
    }
    printf("\n%o\n%o", time_e1, time_e2);
    return 0;
}
