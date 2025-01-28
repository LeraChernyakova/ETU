#include<stdio.h>
#include<stdlib.h>

int abs_max(int arr[], int n) {
  int abs_max=-1; int i;
  for (i=0; i < n; i++) 
    if (abs(arr[i])  > abs(abs_max)) 
      abs_max = arr[i];
  return abs_max;  
}

int abs_min(int arr[], int n) {
  int abs_min=abs(arr[0]); int i;
  for (i=1; i < n; i++) 
    if (abs(arr[i])  < abs(abs_min)) 
      abs_min = arr[i];
  return abs_min;  
}

int diff(int arr[], int n) {
  return abs_max(arr, n) - abs_min(arr, n); 
}

int sum(int arr[], int n){
  int sum=0; int i, index=0;
  for (i=1; i<n; i++) 
    if (abs(arr[i]) > abs(arr[index])) 
      index = i;
  for (i=index; i < n; i++) 
    sum += arr[i];
return sum; 
}

int main(void){
  int action, size=0;
  char s; 
  int arr[100];
  scanf("%d%c", &action, &s);
  while (size <= 100 && s == ' '){
      scanf("%d%c", &arr[size], &s);
      size++;
  }
  
  if (size == 0) 
    printf("Данные некорректны\n");
  else{
     switch (action){
      case 0: 
       printf("%d\n", abs_max(arr, size));
       break;
      case 1:
       printf("%d\n", abs_min(arr, size));
       break;
      case 2:
       printf("%d\n", diff(arr, size));
       break;
      case 3: 
       printf("%d\n", sum(arr, size));
       break;
      default:
       printf("Данные некорректны\n");
       break;
     }
  }
  return 0;
}
