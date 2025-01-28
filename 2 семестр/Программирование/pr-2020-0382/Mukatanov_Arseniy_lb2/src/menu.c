#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int main(){
    int command ;
    scanf("%d\n", &command);
    int a[20];
    int a_size = 0;
    char sym = ' ';
    while(a_size < 20 && sym == ' '){
        scanf("%d%c",&a[a_size++], &sym);
    }
switch(command){
    case 0:
        printf("%d\n", index_first_negative(a,a_size));
        break;
    case 1:
        printf("%d\n", index_last_negative(a,a_size));
        break;
    case 2:
        printf("%d\n", multi_between_negative(a,a_size));
        break;
    case 3:
        printf("%d\n", multi_before_and_after_negative(a,a_size));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
return 0;
}
