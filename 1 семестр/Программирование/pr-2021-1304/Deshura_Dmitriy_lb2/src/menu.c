#include<stdio.h>
#include"index_first_negative.h"
#include"index_last_negative.h"
#include"sum_between_negative.h"
#include"sum_before_and_after_negative.h"

int main(){
    int index_arr, number_of_command, result_of_programm, flag_2 = 0, c = 0, n = 100;
    char ch;
    scanf("%d%c", &number_of_command, &ch);
    int Data_arr[n];

    for(index_arr = 0; index_arr < n; index_arr++){
        if(ch != '\n'){
	    scanf("%d%c", &Data_arr[index_arr], &ch);
            if(Data_arr[index_arr] < 0){
		flag_2++;
	    }
        } else {
	    Data_arr[index_arr] = 0;
	}
    }
    
    if(flag_2 < 2){
        printf("Данные некорректны\n");
        return 0;
    }
    
    switch(number_of_command){
        case 0:
            result_of_programm = index_first_negative(Data_arr, n);
            break;
        case 1:
            result_of_programm = index_last_negative(Data_arr, n);
            break;
        case 2:
            result_of_programm = sum_between_negative(Data_arr, index_first_negative(Data_arr, n), index_last_negative(Data_arr, n));
            break;
        case 3:
            result_of_programm = sum_before_and_after_negative(Data_arr, index_first_negative(Data_arr, n), index_last_negative(Data_arr, n), n);
            break;
        default:
            printf("Данные некорректны\n");
            return 0;
    }
    
    printf("%d\n", result_of_programm);
    
    return 0;
}
