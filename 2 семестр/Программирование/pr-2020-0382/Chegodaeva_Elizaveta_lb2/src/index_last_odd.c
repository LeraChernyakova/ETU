#include <stdlib.h>
int index_last_odd(int arr[], int len ){
    len = len -1;
    for (int i= len; i>=0; i--){
        if((abs(arr[i]))%2==1){
            return i;
        }
    }
}

