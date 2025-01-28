#include <stdio.h>
#include "index_last_odd.h"
int index_last_odd (int a[100], int a_size){
for (int x=(a_size-1); x>=0; x--){
if (a[x]%2!=0){
return x;
}
}
}
