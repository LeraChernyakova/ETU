#include <stdio.h>
#include "index_first_even.h"
int index_first_even(int a[100],int a_size){
for (int x=0; x<a_size; x++){
if(a[x]%2==0){
return x;
}
}
}
