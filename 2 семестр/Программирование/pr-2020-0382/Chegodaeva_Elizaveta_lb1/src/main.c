#include <stdio.h>
#include <stdlib.h>
#define N 100
int index_first_even(int arr[], int len){
    for (int i=0; i<len; i++){
        if((abs(arr[i]))%2==0){
            return i;
        }
    }
}
int index_last_odd(int arr[], int len ){
    len = len -1;
    for (int i= len; i>=0; i--){
        if((abs(arr[i]))%2==1){
            return i;
        }
    }
}
int sum_between_even_odd(int arr[], int len){
    int sum=0;
    for (int i=index_first_even(arr, len); i<index_last_odd(arr, len); i++){
        sum=sum+abs(arr[i]);
    }
    return sum;    
}
int sum_before_even_and_after_odd(int arr[], int len){
    int summ=0;
    for (int i = 0; i < len; i++){
    summ=summ+abs(arr[i]);
    }
    summ=summ-sum_between_even_odd(arr, len);
    return summ;
}
int main(){
    int n;
    scanf("%d", &n);
    int arr[N];
    int len=0;
    int i=0;
    char gap= ' ';
    
    while(i<N && gap==' '){
        scanf("%i%c", &arr[i], &gap);
        len=len+1;
        i=i+1;
    } 
    switch (n){
        case 0:
            printf("%d\n",index_first_even(arr,len));
            break;
        case 1:
            printf("%d\n",index_last_odd(arr,len) );
            break;
        case 2:
            printf("%d\n",sum_between_even_odd(arr,len));
            break;
        case 3:
            printf("%d\n",sum_before_even_and_after_odd(arr,len));
            break;
        default: 
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
