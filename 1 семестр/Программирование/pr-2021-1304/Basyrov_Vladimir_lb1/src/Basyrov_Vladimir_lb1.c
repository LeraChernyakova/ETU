#include <stdio.h>
#include <stdlib.h>
int index_first_even(int s[],int n)
{	for (int i=0;i<n;i++)
		if (!(s[i]%2))
			return i;}

int  index_last_odd(int s[],int n)
{	for (int i=n-1;i>-1;i--)
		if (s[i]%2)
			return i;}

int  sum_between_even_odd(int s[],int n)
{	int start=index_first_even(s,n),finish=index_last_odd(s,n),sum=0;
	for (int i=start;i<finish;i++)
		sum+=abs(s[i]);
	return sum;}

int sum_before_even_and_after_odd(int s[],int n)
{	int start=index_first_even(s,n),finish=index_last_odd(s,n),sum=0;
	for (int i=0;i<start;i++)
		sum+=abs(s[i]);
	for (int i=finish;i<n;i++)
		sum+=abs(s[i]);
	return sum;		}

int main()
{	int s[100]={},i=0,choose;
        char c;
	scanf("%d",&choose);
        do  
                {scanf("%d%c",&s[i],&c);
                i++;}
        while  (c!='\n');
        s[i]='\0';
	switch (choose)
	{	case 0:printf("%d",index_first_even(s,i));
			break;
		case 1:printf("%d",index_last_odd(s,i));
			break;
		case 2:printf("%d",sum_between_even_odd(s,i));
			break;
		case 3:printf("%d",sum_before_even_and_after_odd(s,i));
			break;
		default: printf("данные некорректны");}
}
