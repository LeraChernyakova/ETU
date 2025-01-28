//Kriventsova L.S. 0382
#include <stdio.h>
#include <stdlib.h>
#define max 100
void index_first_zero(int num[max],int length)
{
int i;
for (i = 0; i< length && num[i]!=0; i++)
    {
    }
printf ("\n%d", i);
}

void index_last_zero(int num[max], int length)
{
int i,last=0;
for (i = 0; i < length; i++)
    {if (num[i]==0) last=i;
    }
printf ("\n%d", last);
}

void sum_between(int num[max], int length)
{
int i,sum1=0,sum2=0;
for (i = 0; num[i]!=0; i++)
    {
    } 
while(i<length){
    for (i++; num[i]!=0 && i<length; i++)
        {sum2+=abs(num[i]);
        } 
        if (i<length && num[i]==0){
    sum1=sum2;
    }
}
printf ("\n%d", sum1);
}

void sum_before_and_after(int num[max], int length)
{
int i,sum1=0,sum2=0;
for (i = 0; num[i]!=0; i++)
    {sum1+=abs(num[i]);
    }
for (i++; i<length; i++)
    {
    if (num[i]!=0){
        sum2+=abs(num[i]);
        }
        else {
            sum2=0;
            }
    }
printf ("\n%d", sum1+sum2);
}

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
case '0': index_first_zero(arr,length);
    break; 
case '1': index_last_zero(arr,length);
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
