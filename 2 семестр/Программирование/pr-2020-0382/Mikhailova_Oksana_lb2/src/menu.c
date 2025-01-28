#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define N 100

int main(){
    int arr[N];
    int arr_size = 0;
    char sym = ' ';
    int res0, res1, res2, res3;

    int x;
    scanf ("%d", &x);

    while ((arr_size<N) && (sym == ' ')){
        scanf ("%d%c", &arr[arr_size++], &sym);
    }

    switch (x){
        case 0:
        res0=index_first_negative (arr, arr_size);
        printf ("%d\n", res0);
        break;
        case 1:
        res1=index_last_negative (arr, arr_size);
        printf ("%d\n", res1);
        break;
        case 2:
        res2=sum_between_negative (arr, arr_size);
	printf ("%d\n", res2);
        break;
        case 3:
        res3=sum_before_and_after_negative (arr, arr_size);
        printf ("%d\n", res3);
	break;
        default:
        printf ("Данные некорректны\n");
    }
    return 0;
}
