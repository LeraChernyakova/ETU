#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "sum.h"

int sum(int arr[100],int index){
    int index_max;
    int max = abs_max(arr,index);
    for(int i = 0; i <= index;i++){
        if (max == arr[i]){
                                index_max = i;
                                break;
        }
    }
    int summa = 0;
    for (int j = index_max; j <= index; j++){
        summa += arr[j];
    }
    return summa;
}
