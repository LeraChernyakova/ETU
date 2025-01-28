#include <stdio.h>
#include <stdlib.h>

int abs_max(int array_size, int array[]){
    int max_index = 0;
    for (int i = 1; i < array_size; i++){
        if (abs(array[i]) > abs(array[max_index])){
            max_index = i;
        }
    }
    return max_index;
}

int abs_min(int array_size, int array[]){
    int min_index = 0;
    for (int i = 1; i < array_size; i++){
        if (abs(array[i]) < abs(array[min_index])){
            min_index = i;
        }
    }
    return min_index;
}

int diff(int array_size, int array[]){
    return (array[abs_max(array_size, array)] - array[abs_min(array_size, array)]);
}

int sum(int array_size, int array[]){
    int sum = 0;
    for (int i = abs_max(array_size, array); i < array_size; i++)
        sum += array[i];
    return sum;
}

int main()
{
    int array[101];
    char character;
    int command, array_size = 0;
    scanf("%d%c", &command, &character);
    while (array_size <= 100 && character == ' '){
        scanf("%d%c", &array[array_size], &character);
        array_size++;
    }
    if (array_size == 0)
        printf("Данные некорректны\n");
    else {
        switch(command){
        case 0:
            printf("%d\n", array[abs_max(array_size, array)]);
            break;
        case 1:
            printf("%d\n", array[abs_min(array_size, array)]);
            break;
        case 2:
            printf("%d\n",diff(array_size, array));
            break;
        case 3:
            printf("%d\n", sum(array_size, array));
            break;
        default:
            printf("Данные некорректны\n");
            break;
        }
    }
    return 0;
}
