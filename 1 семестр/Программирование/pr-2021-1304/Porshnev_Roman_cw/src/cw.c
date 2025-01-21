#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

char* read(){

    char c;
    char *string;
    char *temp;
    string = NULL;
    int size = 20;
    int n = 0;
    temp = realloc(string, size * sizeof(char));
    if (temp == NULL){
        printf("Память не выделена!\n");
        return NULL;
    }
    else
        string = temp;
    do{
        if (n == size - 1){
            size += 20;
            temp = realloc(string, (size + 20) * sizeof(char));
            if (temp == NULL){
                printf("Память не выделена!\n");
                return NULL;
            }
            else
                string = temp;
        }
        scanf("%c", &c);
        string[n] = c;
        n += 1;
    }while (c != '\n');
    string[n] = '\0';
    string[n - 1]= '\0';
    return string;
}


unsigned long long int production_of_codes(char *string){

    int i, check = 0;
    unsigned long long int N = ULLONG_MAX, prod = 1;
    double out_of_ull;
    for(i = 0; i < strlen(string); i++){
        out_of_ull = N / string[i];
        if (prod > out_of_ull){
            printf("Произведение кодов символов данной строки больше максимального значения типа unsigned long long int!\n");
            check = 1;
            break;
        }
        if (string[i] != 0)
            prod = prod * string[i];
    }
    if (check == 1)
        return -1;
    else
        return prod;
}

unsigned long long int powered(int n){

    int i;
    unsigned long long int ans = 1;
    for(i = 0; i < n; i++)
        ans = ans * 2;
    return ans;
}
char* from_binary_to_decimal(char *string){

    int i, check = 0, number, j = 0;
    char *ans;
    char *ans_rev;
    char c;
    ans = NULL; ans_rev = NULL;
    unsigned long long int decimal = 0;
    for(i = 0; i < strlen(string); i++){
        if ((string[i] != '1') && (string[i] != '0')){
            printf("Введено число не в двоичной системе счисления!\n");
            check = 1;
            break;
        }
        number = string[i] - '0';
        decimal = decimal + number * powered(strlen(string) - i - 1);
    }
    if (check == 1)
        return "nothing";
    else{
        i = 0;
        while (decimal / 10 > 0){
            number = decimal % 10;
            decimal = decimal / 10;
            c = number + '0';
            ans = realloc(ans, (i + 1) * sizeof(char));
            ans[i] = c;
            i++;
        }
        ans = realloc(ans, (i + 2) * sizeof(char));
        ans[i] = decimal + '0';
        ans[i+1] = '\0';

        for(i = strlen(ans) - 1; i > -1; i--){
            ans_rev = realloc(ans_rev, (j + 1) * sizeof(char));
            ans_rev[j] = ans[i];
            j += 1;
        }
        ans_rev = realloc(ans_rev, (j + 1) * sizeof(char));
        ans_rev[j] = '\0';
        return ans_rev;
    }
}

int out_of_ull(char *string){

    if (strlen(string) > 64)
        return 1;
    return 0;
}


int is_substring_in_string(char *substring, char *string){

    int i, j, k, check;
    for(i = 0; i < strlen(string) - strlen(substring) + 1; i++){
        check = 0;
        j = i;
        for(k = 0; k < strlen(substring); k++){
            if (string[j] != substring[k]){
                check = 1;
                break;
            }
            j += 1;
        }
        if (check == 0)
            return 1;
    }
    return 0;
}

int count_vowels(char *string){

    int i, count = 0;
    for(i = 0; i < strlen(string); i++)
        if (strchr("AEIOUYaeiouy", string[i]) != 0)
            count += 1;
    return count;
}


int main(){

    setlocale(LC_ALL, "Russian");
    int stop = 0;
    char c1, c2;
    char *string;
    char *substring;
    printf("Введите [1], если хотите получить произведение кодов символов строки\n"
           "Введите [2], если хотите получить число в десятичной системе счисления, изначально введённое в двоичной\n"
           "Введите [3], если хотите проверить вхождение одной строки в другую\n"
           "Введите [4], если хотите получить количество гласных в введёной строке\n"
           "Введите [5], если хотите выйти из программы\n");
    while (stop != 1){
        scanf("%c%c", &c1, &c2);
        switch(c1){
            case '1':
                printf("Введите строку: ");
                string = read();
                if (production_of_codes(string) != -1)
                    printf("Произведение кодов символов данной строки: %llu\n", production_of_codes(string));
                free(string);
                break;
            case '2':
                printf("Введите число в двоичнной системе счисления: ");
                string = read();
                if (out_of_ull(string) == 0){
                    if (strcmp(from_binary_to_decimal(string), "nothing") != 0)
                        printf("Число в десятичной системе счисления: %s\n", from_binary_to_decimal(string));
                }
                else {
                    printf("Введённое число выходит за рамки типа unsigned long long int!\n");
                }
                free(string);
                break;
            case '3':
                printf("Введите строку, которая будет проверяться на вхождение в другую строку: ");
                substring = read();
                printf("Введите вторую строку: ");
                string = read();
                if (is_substring_in_string(substring, string))
                    printf("Первая строка входит во вторую\n");
                else
                    printf("Первая строка не входит во вторую\n");
                free(string);
                free(substring);
                break;
            case '4':
                printf("Введите строку: ");
                string = read();
                printf("Количество гласных в строке: %d\n", count_vowels(string));
                free(string);
                break;
            case '5':
                stop = 1;
                break;
            default:
                printf("Функции с таким номером не существует!\n");
        }
    }
    return 0;
}
