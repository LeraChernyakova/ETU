#include <stdio.h>  
#include <time.h>
#include <stdlib.h>

int sort(const void *x1, const void *x2){
return ( *(int*)x1 - *(int*)x2 );}

int main (void){    
 int i,j,x1[1000],x2[1000],xx,end;
 float t1,t2;
 
 // for (i=0;i<1000;i++){x1[i]=rand()%200-100;x2[i]=x1[i];}
 for (i=0;i<1000;i++){scanf("%i",&x1[i]);x2[i]=x1[i];}
 // for (i=0;i<1000;i++){printf("%i ",x1[i]);}printf("\n\n");
 
 t1=clock();
 for (int i = 1000; i >= 0; i--){
    end = 0;
    for (int j = 0; j < i; j++){
        if (x1[j] > x1[j + 1]){
            xx = x1[j];
            x1[j] = x1[j + 1];
            x1[j + 1] = xx;
            end++;}}
    if (end == 0){break;}}
 t1=(clock()-t1)/CLOCKS_PER_SEC;
 
 
 t2=clock();
 qsort(&x2, 1000, sizeof(int), sort); 
 t2=(clock()-t2)/CLOCKS_PER_SEC;
 
 for (i=0;i<1000;i++){printf("%i ",x1[i]);}
 printf("\n%f\n%f",t1,t2);
   return 0;
}

