#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_text(char*** text);
int format_text(int sentences, char*** text);
int cmp(const void* p1, const void* p2);
void print_dates(int sentences, char*** text);
int odd_count(int sentences, char*** text);
int upper_case(int sentence, char*** text);
void lower_case(int sentence, char*** text);
void print_text(int sentence, char*** text);
void free_text(int sentence, char*** text);

int main(){
    printf("Введите строку (для окончания ввода переведите строку два раза):\n");
    char** text = malloc(sizeof(char*));
    int choice, end = 0;
    int text_len = read_text(&text);
    text_len = format_text(text_len, &text);
    while (end == 0){
        printf("Список действий:\n"
                "1. Найти во всем тексте даты и вывести их по возрастанию.\n"
                "2. Удалить все предложения в которых количество слов нечетно.\n"
                "3. Преобразовать все слова в которых нет цифр так, чтобы все буквы кроме последней были прописными.\n"
                "4. Вывести все предложения в которых нет заглавных букв.\n"
                "0. Выход из программы\n\n"
                "Выберите действие: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice){
            case 1:
                print_dates(text_len, &text);
                break;
            case 2:
                text_len = odd_count(text_len, &text);
                print_text(text_len, &text);
                break;
            case 3:
                text_len = upper_case(text_len, &text);
                print_text(text_len, &text);
                break;
            case 4:
                lower_case(text_len, &text);
                break;
            case 0:
                printf("Выход из программы.\n");
                end = 1;
                break;
            default:
                printf("Неверное действие. Повторите ввод.\n");
                break;
        }
        printf("\n");
    }
    free_text(text_len, &text);
    return 0;
}   

int read_text(char*** text){
    int new_lines_count = 0, passed = 1, sentences = 0, count = 0, str_length = 1000;
    char c;
    while (1){
        count = 0;
        (*text) = realloc((*text), sizeof(char*) * (sentences+1));
        if ((*text) == NULL){
            puts("Недостаточно памяти!");
            exit(0);
        }
        (*text)[sentences] = malloc(sizeof(char) * str_length);
        c = getchar();
        if (c == '\n'){
            new_lines_count++;
            if (new_lines_count==2)
                break;
        }
        else{
            (*text)[sentences][count] = c;
            new_lines_count=0;
        }
        do{
            count++;
            c = getchar();
            if (c == '\n'){
                new_lines_count++;
                break;
            }
            else
                new_lines_count = 0;
            (*text)[sentences][count] = c;
            passed = (strchr(".", c) == NULL);
            if (count >= str_length - 2){
                str_length = str_length + 500;
                (*text)[sentences] = (char*) realloc((*text)[sentences], str_length);
                if ((*text)[sentences] == NULL){
                        puts("Недостаточно памяти!");
                        exit(0);
                }
            }
        } while(passed);
        if (new_lines_count == 2)
            break;
        c=getchar();
        if (c == '\n')
                new_lines_count++;
        else
                new_lines_count = 0;
        (*text)[sentences][count+1] = ' ';
        (*text)[sentences][count+2] = '\0';
        sentences++;
    }
    return sentences;
}

int format_text(int sentences, char*** text){
    for(int i = 0; i < sentences; i++){
            int j = i + 1;
            while (j < sentences){
                if (strcasecmp((*text)[i], (*text)[j]) == 0){
                    free((*text)[j]);
                    sentences--;
                    for (int k = j; k <= sentences; k++){
                        (*text)[k] = (*text)[k + 1];
                    }
                }
                else
                    j++;
            }
    }
    return sentences;
}

int cmp(const void* p1, const void* p2){
    const int *a = *(const int**)p1;
    const int *b = *(const int**)p2;
    if (a[2] == b[2]){
        if (a[1] == b[1])
            return a[0] - b[0];
        else 
            return a[1] - b[1];
    }
    else
        return a[2] - b[2];
}

void print_dates(int sentences, char*** text){    // task 1
    int sentence_len, items = -1, j, flag = 0;
    int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
    int** dates = malloc(sizeof(int*));
    char temp[11];
    for (int i = 0; i < sentences; i++){
        sentence_len = 0;
        for (int j = 0; (*text)[i][j]; j++)
            sentence_len++;
        for (j = 0; j <= sentence_len-10; j++){
            if ((*text)[i][j] == 'd' && (*text)[i][j+3] == 'm' && (*text)[i][j+6] == 'y' &&
                isdigit((*text)[i][j+1]) && isdigit((*text)[i][j+2]) && 
                isdigit((*text)[i][j+4]) && isdigit((*text)[i][j+5]) && 
                isdigit((*text)[i][j+7]) && isdigit((*text)[i][j+8]) && isdigit((*text)[i][j+9]) && isdigit((*text)[i][j+10])){
                    flag = 1;
                    items++;    
                    dates = realloc(dates, sizeof(int*) * (items+1));
                    if (dates == NULL){
                        puts("Недостаточно памяти!");
                        exit(0);
                    }
                    for (int g = 0; g < 11; g++)
                        temp[g] = (*text)[i][j+g];
                    dates[items] = calloc(3, sizeof(int));
                    sscanf(temp, "d%dm%dy%d", &dates[items][0], &dates[items][1], &dates[items][2]);
            }
        }
    }
    if (flag){
        qsort(dates, items+1, sizeof(int*), cmp);
        for (int i = 0; i <= items; i++){
            if (dates[i][0] < 10)
                flag1 = 1;
            if (dates[i][1] < 10)
                flag2 = 1;
            if (dates[i][2] < 1000)
                flag3 = 1;
            if (dates[i][2] < 100)
                flag4 = 1;
            if (dates[i][2] < 10)
                flag5 = 1;
            printf("%c%d:%c%d:%c%c%c%d\n", '0'*flag1, dates[i][0], '0'*flag2, dates[i][1], '0'*flag3, '0'*flag4, '0'*flag5, dates[i][2]);
            flag1 = 0; flag2 = 0; flag3 = 0; flag4 = 0; flag5 = 0;
        }
        for(int i = 0; i < items; i++)
            free((dates)[i]);
    }
    else
        puts("В тексте не найдено дат!");
    free(dates);
}

int odd_count(int sentences, char*** text){       // task 2
    int count;
    for (int i = 0; i < sentences; i++){
        count = 0;
        for (int j = 0; (*text)[i][j]; j++){
            if ((*text)[i][j] == ' ')
                count++;       
        }
        if (count % 2){
            free((*text)[i]);
            sentences--;
            for (int k = i; k <= sentences; k++){
                (*text)[k] = (*text)[k + 1];
            }
        }
    }
    return sentences;
}

int upper_case(int sentence, char*** text){     // task 3
    int word_len, num_count;
    char c;
    for (int i = 0; i < sentence; i++){
        word_len = 0;
        num_count = 0;
        for (int j = 0; (*text)[i][j]; j++){
            if ((*text)[i][j] != ' ')
                word_len++;
                if (isdigit((*text)[i][j])){
                    num_count++;
                }
            if ((*text)[i][j] == ' '){
                if (num_count == 0){
                    for (int k = j-word_len; k < j; k++){
                            (*text)[i][k] = toupper((*text)[i][k]);    
                    }
                    for (int k = j - 1; k >= j-word_len; k--){
                        if (isalpha((*text)[i][k])){
                            (*text)[i][k] = tolower((*text)[i][k]);
                            break;
                        }
                    }
                }
                word_len = 0;
                num_count = 0;
            }           
        }
    }
    return sentence;
}

void lower_case(int sentence, char*** text){     // task 4
    int failed, flag = 0;
    for (int i = 0; i < sentence; i++){
        failed = 0;
        for (int j = 0; (*text)[i][j]; j++){
            if (isupper((*text)[i][j]))
                failed = 1;
        }
        if (failed == 0){
            printf("%s", (*text)[i]);
        } else
            flag++;
    }
    if (flag == sentence)
        printf("В тексте нет предложений, в которых нет заглавных букв!");
    printf("\n");
}

void print_text(int sentence, char*** text){
    for (int i = 0; i < sentence; i++)
        printf("%s", (*text)[i]);
    printf("\n");
}

void free_text(int sentence, char*** text){
    for(int i = 0; i < sentence; i++)
		free((*text)[i]);
	free(*text);
}