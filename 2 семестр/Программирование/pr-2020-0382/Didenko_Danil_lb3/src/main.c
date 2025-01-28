#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Функция для получение предложения в массив предложений
char* get_sentence(){
    int size = 10;
    char* sent = (char*)malloc(size *sizeof(char));
    int count_let = 0;
    int is_begin = 1;//Начало ли предложения
    while(1){
        if (count_let == size-1){
            char* tmp = (char*)realloc(sent,(size+10)*sizeof(char));
            sent = tmp;
            size+=10;
        }
        sent[count_let] = (char)getchar();//Запись букв в предложение

        //Исключение табуляции и пробелов
        if (sent[count_let] == ' ' || sent[count_let] == '\t' || sent[count_let] == '\n'){
            if (is_begin){count_let--;}//Если запрещенные символы и начало, то остаемся на том же индексе(дальше будет++)
        }else{is_begin = 0;}//Иначе отмечаем, что уже не начало предложения


        //Условие окончания предложения
        if (sent[count_let] == '.'||
            sent[count_let] == ';'||
            sent[count_let] == '?'||
            sent[count_let] == '!' ){break;}
        count_let++;

    }
    sent[count_let+1] = '\0';
    return sent;
}

int is_equal(char* str1, char* str2){
    int flag = 1;
    for (int i = 0;i<strlen(str2);i++){
        if (str1[i] != str2[i]){
            flag = 0;
        }
    }
    return flag;
}

int is_sent_valid(char* sent){
    int i = 0;
    int count_5 = 0;
    while (sent[i] != '\0'){
        if(sent[i] == 53){
            count_5++;
            i++;
        }else if ((sent[i] > 47 && sent[i] < 58) || (sent[i]>64 && sent[i] < 91) || (sent[i]>96 && sent[i] < 123)){
            count_5 = 0;
            i++;
        }else {
            if(count_5 == 3){
                return 0;
            }else{
                count_5 = 0;
                i++;
            }
        }
    }
    if(count_5 == 3){return 0;}else{return 1;}
}

int main() {
    int size_txt = 20;
    char** text = malloc(size_txt*sizeof(char*));
    char* stop_sent = "Dragon flew away!";
    int count_sent = 0;//Конечное количество предложений
    int count_sent_b = 0;//Начальное количество предложений
    while(1){
        if (count_sent == size_txt){
            char** tmp = (char**)realloc(text,(size_txt+20)*sizeof(char*));
            text = tmp;
            size_txt+=20;
        }

        char* sent = get_sentence();
        if (is_sent_valid(sent)){
            text[count_sent] = sent;
            if (is_equal(text[count_sent],stop_sent)){
                break;}
            count_sent++;
            count_sent_b++;
        }else{
            count_sent_b++;
        }
    }

    for(int i = 0;i<=count_sent;i++){
        printf("%s\n",text[i]);
    }

    for (int i=0; i < count_sent;i++){
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d",count_sent_b,count_sent);
    return 0;
}