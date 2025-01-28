#include "diff.h"
#include "max.h"
#include "min.h"
int diff(int ar[], int len){
    int ans = max(ar, len) - min(ar, len);
    return ans;
}
