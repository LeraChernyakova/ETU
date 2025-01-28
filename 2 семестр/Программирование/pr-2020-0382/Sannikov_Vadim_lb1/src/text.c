#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int fnumb[], int length){
    int i;
    for (i=0; i<length && fnumb[i]!=0; i++){
    }
    return i;
}

int index_last_zero(int fnumb[], int length){
    int i, thelast=0;
    for (i=0; i<length; i++){
        if (fnumb[i]==0) thelast = i;
    }
    return thelast;
}

int sum_between(int fnumb[], int length){
    int i, sum1=0, sum2=0;
    for (i=0;fnumb[i]!=0;i++){
    }
    while (i<length){
        for (i++; i<length && fnumb[i]!=0; i++){
            sum2+=abs(fnumb[i]);
        }
            if (i<length && fnumb[i]==0)
            sum1=sum2;
    }
    return sum1;
}

int sum_before_and_after(int fnumb[], int length){
    int i, sum1=0, sum2=0;
    for (i=0; fnumb[i]!=0; i++){
        sum1+=abs(fnumb[i]);
    }
    for (i++; i<length; i++){
        if (fnumb[i]!=0){
            sum2+=abs(fnumb[i]);
        }
        else{
            sum2=0;
        }
    }
    return sum1 + sum2;
}

int main(){
    int numb[100], length=0, symbol;
    char prob = ' ';
    
    scanf("%d", &symbol);
    
    while (length < 100 && prob == ' '){
        scanf("%d%c", &numb[length], &prob);
        length++;
    }
    switch(symbol){
case 0: printf("%d", index_first_zero(numb,length));
    break; 
case 1: printf("%d", index_last_zero(numb,length));
    break; 
case 2: printf("%d", sum_between(numb,length));
    break; 
case 3: printf("%d", sum_before_and_after(numb,length));
    break; 
default:printf ("Данные некорректны");
    break;
}
    return 0;
}
