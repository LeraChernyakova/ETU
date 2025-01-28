#include "sum.h"
#include "min.h"
int sum(int ar[], int len){
    int ans = 0;
    for(int i = 0; ar[i] != min(ar, len); i++){
            ans += ar[i];
    }
    return ans;
}
