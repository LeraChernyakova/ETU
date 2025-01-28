#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

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
