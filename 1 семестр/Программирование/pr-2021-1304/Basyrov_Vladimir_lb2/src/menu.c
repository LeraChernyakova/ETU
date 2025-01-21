#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "sum_before_even_and_after_odd.h" 

int main()
{       int s[100]={},i=0,choose;
        char c;
        scanf("%d",&choose);
        do  
                {scanf("%d%c",&s[i],&c);
                i++;}
        while  (c!='\n');
        s[i]='\0';

        switch (choose)
        {       case 0:printf("%d",index_first_even(s,i));
                        break;
                case 1:printf("%d",index_last_odd(s,i));
                        break;
                case 2:printf("%d",sum_between_even_odd(s,i));
                        break;
                case 3:printf("%d",sum_before_even_and_after_odd(s,i));
        		 break;
                default:printf("Данные некорректны");}
        printf("\n");}
