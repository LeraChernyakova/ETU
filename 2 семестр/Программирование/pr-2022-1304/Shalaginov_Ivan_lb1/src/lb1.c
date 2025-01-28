#include <stdio.h>
#include <stdlib.h>

int compar(const void * a, const void * b)
{
if ( abs(*(int*)a) > abs(*(int*)b) ) return -1;
if ( abs(*(int*)a) == abs(*(int*)b) ) return 0;
if ( abs(*(int*)a) < abs(*(int*)b) ) return 1;
}

int main(){
int* arr = malloc(1000*sizeof(int));
char c;
for(int i = 0; i < 1000; i++){
scanf("%d%c", &arr[i], &c);
};
clock_t t;
t = clock();
qsort(arr, 1000, sizeof(int), compar);
t = clock() - t;
for (int i = 0; i < 1000; i++){
printf("%d ", arr[i]);
}
printf("\n");
printf("%f\n", t);
return 0;
}