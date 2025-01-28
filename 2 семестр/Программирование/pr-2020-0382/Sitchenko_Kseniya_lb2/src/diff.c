#include"abs_min.h"
#include"abs_max.h"

int diff(int arr[], int n) {
  return abs_max(arr, n) - abs_min(arr, n); 
}
