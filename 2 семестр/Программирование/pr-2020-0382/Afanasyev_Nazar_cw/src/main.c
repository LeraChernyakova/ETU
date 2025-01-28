#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <math.h>

#define RED "\033[0;101;37m"
#define GREEN "\033[0;102;37m"
#define NONE  "\033[0;m"

char* getSentence(){
    int sentenceSize = 40;
    char* sentence = malloc(sentenceSize);
    char sym; int count = 0;
    while(1){
        sym = getchar();
        sentence[count++] = sym;
        if(count == sentenceSize){ sentenceSize += 15; sentence = realloc(sentence, sentenceSize); }
        if(sym == '.') break;
    }
    sentence[count] = '\0'; 
    return sentence;
}

char** getText(int* size){
    int textSize = 20;
    char** text = calloc(textSize, sizeof(char*));
    char* sentence; int count = 0;
    while(1){
        sentence = getSentence();
        text[count++] = sentence;
        if(getchar() == '\n') break;
        if(count == textSize){ textSize += 10; text = realloc(text, textSize * sizeof(char*)); }
    }
    *size = count; return text;
}

char* firstWord(char* sentence){
    int wordSize = 20;
    char* word = malloc(wordSize);
    char sym; int count = 0;
    while(1){
        sym = sentence[count];
        if (sym == ' ' || sym == ',' || sym == '.'){ 
            word[count] = '\0';
            break;
        }
        else word[count++] = sym;
        if(count == wordSize){ wordSize += 30; word = realloc(word, wordSize); } 
    }
    return word;
}

char* lastWord(char* sentence){
    int size = -1;
    while(sentence[size+1] != '.') size++;

    short wordSize = 30;
    char* word = malloc(wordSize);
    char sym; short count = 0;
    while(1){
        sym = sentence[size-count];
        if (sym == ' ' || sym == ','){ 
            word[count] = '\0';
            break;
        }
        else word[count++] = sym;
        if(size-count == -1){
            word[count] = '\0';
            break;
        }
        if(count == wordSize){
            wordSize += 30;
            word = realloc(word, wordSize);
        } 
    }
    strrev(word);
    return word;
}

char** removeDuplicate(char** text, int* size){
    char** updatedText = calloc(*size, sizeof(char*));
    int count = 0; short areSame;
    for(int i = 0; i < *size; i++){
        short isDuplicate = 0;
        for(int j = 0; j < i; j++){
            if(strlen(text[i]) == strlen(text[j])){
                areSame = 1;
                for(int n = 0; n < strlen(text[i]); n++){
                    if(toupper(text[i][n]) != toupper(text[j][n])){
                        areSame = 0; break;
                    }
                }
                if(areSame){
                    isDuplicate = 1; break;
                }
            }
        }
        if(!isDuplicate) updatedText[count++] = text[i];
    }
    *size = count; return updatedText;
}

char** changeDate(char** text, int* size){
    char** updatedText = calloc(*size, sizeof(char*));
    char* updatedSentence; char sym; int count;
    for(int i = 0; i < *size; i++) {
        updatedSentence = malloc(sizeof(text[i])); count = 0;
        for(int j = 0;;j++){
            sym = text[i][j];
            if(isdigit(sym)){
                char* data = malloc(11);
                strncpy(data, &text[i][j], 11);

                int year, day; char month[4];
                if((sscanf(data, "%4d %3s %2d", &year, month, &day)) == 3){
                    month[3] = '\0';
                    short month_i =  !strcmp(month, "Jan") ? 0 : !strcmp(month, "Feb") ? 1 : !strcmp(month, "Mar") ? 2 : !strcmp(month, "Apr") ? 3 : !strcmp(month, "May") ? 4 : !strcmp(month, "Jun") ? 5 : !strcmp(month, "Jul") ? 6 : !strcmp(month, "Aug") ? 7 : !strcmp(month, "Sep") ? 8 : !strcmp(month, "Oct") ? 9 : !strcmp(month, "Nov") ? 10 : 11;

                    struct tm time1 = {0};          struct tm time2 = {0};
                    time1.tm_year = year-1900;      time2.tm_year = year-1899;
                    time1.tm_mon = month_i;         
                    time1.tm_mday = day;            time2.tm_mday = 1;
                    time_t t1 = mktime(&time1);     time_t t2 = mktime(&time2);

                    int diff = (int) difftime(t2, t1) / 3600;
                    short numCount = diff > 0 ? floor(log10(diff)) + 1 : 1;
                    char diff_s[numCount]; 
                    itoa(diff, diff_s, 10);

					diff_s[numCount] = '\0';
                    updatedSentence[count] = '\0';
                    strcat(updatedSentence, diff_s);

                    count += numCount;
                    j+=10; continue;
                }
				free(data);
            }          
            updatedSentence[count++] = sym;
            if(sym == '.') { 
                updatedSentence[count] = '\0'; 
                break; 
            }
        }
        updatedText[i] = updatedSentence;
    }
    return updatedText;
}

char** colorize(char** text, int* size){
    char** updatedText = calloc(*size, sizeof(char*));
    int sentenceSize; char* updatedSentence;
    int count; char sym; short isOdd; short noWord;

    isOdd = 1;
    for(int i = 0; i < *size; i++) {
        sentenceSize = 30; 
        updatedSentence = malloc(sentenceSize);
        count = 0; noWord = 1;
        for(int j = 0;;j++){
            sym = text[i][j];
            if ((sym == ' ' || sym == ',' || sym == '.')){
                if(!noWord){
                    updatedSentence[count] = '\0';
                    strcat(updatedSentence, NONE);
                    count += strlen(NONE);
                    noWord = 1;
                    isOdd = !isOdd;
                }
            }else if(noWord){
                noWord = 0;
                updatedSentence[count] = '\0';
                strcat(updatedSentence, isOdd ? GREEN : RED);
                count += strlen(GREEN);
            }
            updatedSentence[count++] = sym;

            if(count >= sentenceSize - 20){ sentenceSize += 30; updatedSentence = realloc(updatedSentence, sentenceSize); } 
            if(sym == '.') { 
                updatedSentence[count] = '\0'; 
                break; 
            }
        }
        updatedText[i] = updatedSentence;
    }
    return updatedText;
}

char** removeSimilarities(char** text, int* size){
    char** updatedText = calloc(*size, sizeof(char*));
    int count = 0;
    for(int i = 0; i < *size; i++) {
        char* first = firstWord(text[i]);
        char* last = lastWord(text[i]);
        for(int j = 0; j < strlen(first); j++) first[j] = tolower(first[j]);
        for(int j = 0; j < strlen(last); j++) last[j] = tolower(last[j]);
        
        if(strcmp(first, last)) updatedText[count++] = text[i];
		free(first); free(last);
    }
    *size = count; return updatedText;
}

int cmpfunc (const void* pa, const void* pb) {
    int* arr1 = (int*)pa;
    int* arr2 = (int*)pb;
    int diff1 = arr1[0] - arr2[0];
    if (diff1) return diff1;
    return arr1[1] - arr2[1];
}

char** sort(char** text, int* size){
    int array[*size][2]; int sum; char* word;
    for(int i = 0; i < *size; i++){
        sum = 0; word = firstWord(text[i]);
        for(int j = 0; j < strlen(word); j++) sum += word[j];
        array[i][0] = sum; array[i][1] = i;
    }
    qsort(array, *size, sizeof(array[0]), cmpfunc);

    char** updatedText = calloc(*size, sizeof(char*));
    for(int i = 0; i < *size; i++){
        updatedText[i] = text[array[i][1]];
    }
    return updatedText;
}

void solve(short operation, char*** text, int size, char** (*f)(char**, int*)){
    wprintf(L"\nОперация %hd:\n", operation);
    int newSize = size;
    char** temp = f(*text, &newSize);
    for(int i = 0; i < newSize; i++) {
        printf("%s ", temp[i]);
        free(temp[i]);
    }
    for(int i = 0; i < size; i++) free((*text)[i]);
    free(temp); free(*text);
    printf("\n");
}

void showMenu(){
    wprintf(L"\n\t\t\t\t\tДоступные операции:\n");
    wprintf(L"\t1: Найти в предложениях все даты записанные в виде “<год> <месяц> <day>” (“1886 Jun 03”)\n\t\t и заменить их на строку показывающую сколько осталось часов до конца года.\n");
    wprintf(L"\t2: Вывести все строки выделив слова на четных позициях красным цветом, а на нечетных зеленым.\n");
    wprintf(L"\t3: Удалить все предложения, которые начинаются и заканчиваются на одно и то же слово.\n");
    wprintf(L"\t4: Отсортировать предложения по увеличению сумме кодов символов первого слова в предложении.\n");
    wprintf(L"\t5: Выход.\n\n");
}

int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Введите текст: ");
    int size; char** text;

    text = getText(&size);
    char** tmp = removeDuplicate(text, &size);
    free(text); text = tmp;

    wprintf(L"\n\nПосле удаления повторений: ");
    for(int i = 0; i < size; i++) printf("%s ", text[i]);
    printf("\n");

    showMenu();
    wprintf(L"Выберите операцию: ");
    short operation; scanf("%hd", &operation);
    
    switch (operation)
    {
        case 1: solve(operation, &text, size, changeDate); break;
        case 2: solve(operation, &text, size, colorize); break;
        case 3: solve(operation, &text, size, removeSimilarities); break;
        case 4: solve(operation, &text, size, sort); break;
        case 5: wprintf(L"Выход\n"); break;
        default: wprintf(L"Ошибка: номер операции может быть только от 1 до 5\n"); break;
    }
    return 0;
}