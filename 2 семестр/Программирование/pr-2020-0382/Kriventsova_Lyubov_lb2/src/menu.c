#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#define max 100
int main ()
{
char command;
int arr[max],length=0;
char sym = ' ';

command = getchar ();
while (length < max && sym == ' ')
    {
    scanf ("%d%c", &arr[length++], &sym);
    }
switch(command){
case '0': printf ("\n%d", index_first_zero(arr,length));
    break; 
case '1': printf ("\n%d", index_last_zero(arr,length));
    break; 
case '2': sum_between(arr,length);
    break; 
case '3': sum_before_and_after(arr,length);
    break; 
default:printf ("Данные некорректны");
    break;
}
return 0;
}
