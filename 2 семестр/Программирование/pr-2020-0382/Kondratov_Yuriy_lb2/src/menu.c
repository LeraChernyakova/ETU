#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
int main(){
    
    int array[100], index = 0, option;
    char c = ' ';
    
    scanf("%d", &option);
    
    while(index < 100 && c == ' '){
        scanf("%d%c", &array[index++], &c);
    }
    
    switch (option){
        case 0:
            printf("%d\n", max(array, index));
            break;
        case 1:
            printf("%d\n", min(array, index));
            break;
        case 2:
            printf("%d\n", diff(array, index));
            break;
        case 3:
            printf("%d\n", sum(array, index));
            break;
        default:
            printf("Данные некорректны\n");
    }
    
    return 0;
}
