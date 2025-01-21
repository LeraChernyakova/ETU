#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
# define Nu 100
int main(){
    int arr[Nu],N=0,a;
    int ans_max,ans_min,ans_sum,ans_diff;
    char c;
    scanf("%d",&a);
    
   
     while(N<=Nu){   
         scanf("%d%c",&arr[N],&c);
         N++;
         if(c=='\n')break;
      }
   
      

    ans_max=abs_max(arr,N);
    ans_min=abs_min(arr,N);
    ans_sum=sum(arr,N);
    ans_diff=diff(arr,N);
   
    switch(a){
        case 0:
        printf("%d\n",ans_max);
        break;
    
        case 1:
        printf("%d\n",ans_min);
        break;
    
        case 2:
        printf("%d\n",ans_diff);
        break;
    
        case 3:
        printf("%d\n",ans_sum);
        break;
    
        default: puts("Данные некорректны\n");
    
    }
    return 0;
    
}
