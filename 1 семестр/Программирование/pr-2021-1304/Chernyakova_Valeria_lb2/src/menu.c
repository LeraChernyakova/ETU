#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int arr[100], ind = 0, n = 0;
    char symb;
    scanf ("%d", &n);
    while (symb != '\n'){
        scanf ("%d%c", &arr[ind], &symb);
        ind++;
    }
    switch (n){
        case 0:
            printf ("%d\n", max(arr, ind));
            break;
        case 1:
            printf ("%d\n", min(arr, ind));
            break;
        case 2:
            printf ("%d\n", diff(arr, ind));
            break;
        case 3:
            printf ("%d\n", sum(arr, ind));
            break;
        default: 
            printf ("Данные некорректны\n");
            break;
    }
}
