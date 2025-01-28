#include "min.h"
int min(int ar[], int len){
    int res = ar[0];
    for (int j = 1; j < len; j++){
        if (ar[j] < res){
           res = ar[j];
        }
    }
    return res;
}
