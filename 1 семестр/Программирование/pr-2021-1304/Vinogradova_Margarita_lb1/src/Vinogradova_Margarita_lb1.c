#include <stdio.h>
#include <stdlib.h>

# define Nu 100

int max_abs(int arr[],int N){
    int max=0;
	for(int i=0;i<N;i++){
		if(abs(max)<abs(arr[i])) max=arr[i];
	}
   return max;
}

int min_abs(int arr[],int N){
	int min=1000000;
	for(int i=0;i<N;i++){
		if(abs(min)>abs(arr[i])) min=arr[i];
	}
   return min;
	
}


int sum(int arr[],int N){
	int sum=0,max=0,num;
	
	for(int i=0;i<N;i++){
		
	//	printf("%d %d\n",i,arr[i]);
		
		if(abs(max)<abs(arr[i])){
			max=arr[i];	
			num=i;
		}
		
	}
	for(int i=num;i<N;i++){
		sum=sum + arr[i];
		
	}
	
   return sum;
	
}

int diff(int arr[],int N){
	int diff;
	int max = max_abs(arr,N);
	int min = min_abs(arr,N);
	diff= max-min;
	
   return diff;
	
}



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
   
      
    ans_max=max_abs(arr,N);
    ans_min=min_abs(arr,N);
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
    	
    	default: puts("Данные некоректны\n");
    	
    }
    return 0;
    
}








  


