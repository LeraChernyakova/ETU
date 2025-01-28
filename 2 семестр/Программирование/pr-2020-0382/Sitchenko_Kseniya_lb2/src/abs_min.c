
#include<stdlib.h>

int abs_min(int arr[], int n) {
  int abs_min=abs(arr[0]); int i;
  for (i=0; i < n; i++) 
    if (abs(arr[i])  < abs(abs_min)) 
      abs_min = arr[i];
  return abs_min;  
}

