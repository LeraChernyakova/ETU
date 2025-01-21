#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int find_index_first_even(int array[],int array_length);
int find_index_last_odd(int array[],int array_length);
void output_sum_between_even_odd(int array[],int index_first_even, int index_last_odd);
void output_sum_before_even_and_after_odd(int array[],int array_length,int index_first_even, int index_last_odd);
int main()
{
    int i,task_value,array_length,index_first_even,index_last_odd;
    char sep;
    int array[100];
    array_length=0;
    scanf("%d",&task_value);
    if (task_value>3){
        printf("Данные некорректны\n");
    }
    for(i=0;i<100;i++){
        scanf("%d%c", &array[i],&sep);
        array_length++;
        if(sep=='\n')
            break;
    }
    index_first_even=find_index_first_even(array,array_length);
    index_last_odd=find_index_last_odd(array,array_length);
    switch(task_value){
        case 0:
            if(index_first_even!=-1){
                printf("%d\n",index_first_even);
            }
            else{
                printf("Данные некорректны\n");
            }
            break;
        case 1:
            if(index_last_odd!=-1){
                printf("%d\n",index_last_odd);
            }
            else{
                printf("Данные некорректны\n");
            }
            break;
        case 2:
            output_sum_between_even_odd(array,index_first_even,index_last_odd);
            break;
        case 3:
            output_sum_before_even_and_after_odd(array,array_length,index_first_even,index_last_odd);
            break;
    }
    return 0;
}
int find_index_first_even(int array[],int array_length)
{
    int i,index_first_even;
    index_first_even=-1;
    for(i=0;i<array_length;i++){
        if (abs(array[i])%2==0){
            index_first_even=i;
            break;
        }
    }
    return index_first_even;
}

int find_index_last_odd(int array[],int array_length)
{
    int i,index_last_odd;
    index_last_odd=-1;
    for(i=0;i<array_length;i++){
        if(abs(array[i])%2==1){
            index_last_odd=i;
        }
    }
    return index_last_odd;
}

void output_sum_between_even_odd(int array[],int index_first_even, int index_last_odd)
{
    int i,sum_between_even_odd;
    sum_between_even_odd=0;
    if (((index_first_even==-1) || (index_last_odd==-1)) || (index_last_odd-index_first_even<0)){
        printf("Данные некорректны\n");
    }
    else{
        for(i=index_first_even;i<index_last_odd;i++){
            sum_between_even_odd+=abs(array[i]);
        }
        printf("%d\n",sum_between_even_odd);
    }
}

void output_sum_before_even_and_after_odd(int array[],int array_length,int index_first_even, int index_last_odd){
    int i,sum_before_even_and_after_odd=0;
    if ((index_first_even!=-1) || (index_last_odd!=-1)){
        for(i=0;i<index_first_even;i++){
            sum_before_even_and_after_odd+=abs(array[i]);
        }
		for(i=index_last_odd;i<array_length;i++){
            sum_before_even_and_after_odd+=abs(array[i]);
        }
		    printf("%d\n",sum_before_even_and_after_odd);
    }
	else{
		printf("Данные некорректны\n");
	}
}
