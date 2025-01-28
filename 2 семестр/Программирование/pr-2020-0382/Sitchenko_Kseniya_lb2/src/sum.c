#include<stdlib.h>

int sum(int arr[], int n){
  int sum=0; int i, index=0;
  for (i=1; i<n; i++) 
    if (abs(arr[i]) > abs(arr[index])) 
      index = i;
  for (i=index; i < n; i++) 
    sum += arr[i];
return sum; 
}
