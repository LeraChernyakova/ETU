#include<stdlib.h>

int abs_max(int arr[], int n) {
  int abs_max=-1; int i;
  for (i=0; i < n; i++) 
    if (abs(arr[i])  > abs(abs_max)) 
      abs_max = arr[i];
  return abs_max;  
}
