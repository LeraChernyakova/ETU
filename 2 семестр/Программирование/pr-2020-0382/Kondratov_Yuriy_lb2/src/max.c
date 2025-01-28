#include "max.h"
int max(int ar[], int len){
    int ans = ar[0];
    for (int i = 1; i < len; i++){
        if (ar[i] > ans){
           ans = ar[i];
        }
    }
    return ans;
}
