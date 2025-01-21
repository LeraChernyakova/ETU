#include <stdio.h>

int index_first_negative(int Data_arr[], int n){
    for(int i = 0; i < n; i++){
        if (Data_arr[i] < 0){
            return i;
        }
    }
}

int index_last_negative(int Data_arr[], int n){
    int result;
    for(int i = 0; i < n; i++){
        if (Data_arr[i] < 0){
            result = i;
        }
    }
    return result;
}

int sum_between_negative(int Data_arr[], int index_first_negative, int index_last_negative){
    int sum = 0;
    for(int index_arr = index_first_negative; index_arr < index_last_negative; index_arr++){
        if(Data_arr[index_arr] < 0){
            sum = sum - Data_arr[index_arr];
        }else{
            sum = sum + Data_arr[index_arr];
        }
    }
    
    return sum;
}

int sum_before_and_after_negative(int Data_arr[], int index_first_negative, int index_last_negative, int n){
    int sum = 0;
    for(int index_arr = 0; index_arr < index_first_negative; index_arr++){
        if(Data_arr[index_arr] < 0){
            sum = sum - Data_arr[index_arr];
        }else{
            sum = sum + Data_arr[index_arr];
        }
    }
    for(int index_arr = index_last_negative; index_arr < n; index_arr++){
        if(Data_arr[index_arr] < 0){
            sum = sum - Data_arr[index_arr];
        }else{
            sum = sum + Data_arr[index_arr];
        }
    }
    return sum;
}

int main(){
    int number_of_command, result_of_programm, flag_2 = 0, c = 0, n = 100;
    char ch;
    scanf("%d%c", &number_of_command, &ch);
    int Data_arr[n];

    for(int index_arr = 0; index_arr < n; index_arr++){
        scanf("%d%c", &Data_arr[index_arr], &ch);
        if(Data_arr[index_arr] < 0){
            flag_2++;
        }
        if(ch == '\n'){
            c = index_arr;
            break;
        }
    }
    
    for(int index_arr = c + 1; index_arr < n; index_arr++){
        Data_arr[index_arr] = 0;
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
