#include <stdio.h>
#include <stdlib.h>

int index_first_even(int list[], int listsize){
    for (int i = 0; i < listsize; i++){
        if(list[i]%2==0) {
            return i;
        }   
    }
}


int index_last_odd(int list[], int listsize){
    for (int i = listsize - 1; i >= 0; i--){
        if(abs(list[i])%2==1) {
            return i;
        }   
    }
}

int sum_between_even_odd(int list[], int listsize){
    int res = 0;
    
    for (int i = index_first_even(list, listsize); i < index_last_odd(list, listsize); i++){
      res += abs(list[i]);
    }
    
    return res;
}

int sum_before_even_and_after_odd(int list[], int listsize){
    int sum = 0;

    for (int i = 0; i < listsize; i++) sum += abs(list[i]);

    return sum - sum_between_even_odd(list, listsize); 
}
int main(){
    int n = -1, list[100]; // n - значение для функции, list - список для вводимых символов
    int listsize = 0; // насколько массив заполнен

    char sym = ' ';
    while(listsize<100 && sym == ' '){ //Ввод
        if (n == -1) scanf("%d%c", &n, &sym);
        else scanf("%d%c", &list[listsize++], &sym);
    }

    switch (n)
    {
    case 0:
        printf("%d\n", index_first_even(list, listsize));
        break;
    case 1:
        printf("%d\n", index_last_odd(list, listsize));
        break;
    case 2:
        printf("%d\n", sum_between_even_odd(list, listsize));
        break;
    case 3:
        printf("%d\n", sum_before_even_and_after_odd(list, listsize));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    return 0;
}
