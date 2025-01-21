#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int error_check(int new_sent_count, char** txt,int f);
void sort_sentenses(int new_sent_count, char*** txt);
int cmp(const void* a,const void* b);
void print_soon_and_late_date(int new_sent_count, char** txt);
int delete_sentenses_of_19th_century(int new_sent_count, char** txt);
void print_sentenses_with_curent_date(int new_sent_count,char** txt);
int delete_sent(int sent_count, char*** txt);
int read_arr(char* sent_sep, char*** txt);
void free_txt(int new_sent_count, char*** txt);
void print(char** text, int new_sent_count);
char main(){
        puts("Введите строку.Если вы желаете прекратить ввод, введите пустую строку.");
        int comand = 0;
        int f = 0;
        char** txt = malloc(sizeof(char*));
        char* sent_sep = ".";
        int sent_count = read_arr(sent_sep, &txt);
        int new_sent_count = delete_sent(sent_count, &txt);
        error_check(new_sent_count, txt, f);
        switch(f){
                case 1:
                {
                        exit(0);
                        break;
                }
                case 0:
                {
                        print(txt, new_sent_count);
                        while(1){
                        puts("1 - Вывести все предложения в которых есть дата с текущим годом и месяцем.");
                        puts("2 - Отсортировать предложения по увеличению минимальной даты в них.");
                        puts("3 - Удалить все предложения в которых все даты относятся к 19 веку.");
                        puts("4 - Для каждого предложения вывести самую раннюю и позднюю дату.");
                        puts("5 - Выход.");
                        puts("\n");
                        scanf("%d",&comand);
                        switch(comand){
                                case 1 :
                                {       puts("\n");
                                        print_sentenses_with_curent_date(new_sent_count,txt);
                                        puts("\n");
                                        break;
                                }
                                case 2:{
                                        puts("\n");
                                        sort_sentenses(new_sent_count,&txt);
                                        print(txt,new_sent_count);
                                        puts("\n");
                                        break;
                                }
                                case 3:
                                {
                                        delete_sentenses_of_19th_century(new_sent_count,txt);
                                        print(txt,new_sent_count);
                                        puts("\n");
                                        break;
                                }
                                case 4:
                                {       puts("\n");
                                        print_soon_and_late_date(new_sent_count,txt);
                                        puts("\n");
                                        print(txt,new_sent_count);
                                        puts("\n");
                                        break;
                                }
                                case 5:
                                {
                                        return 0;
                                }
                                default:
                                return 0;
                                }
                        }
                }
        }
        free_txt(new_sent_count, &txt);
        return 0;
}
int read_arr(char* sen_sep, char*** txt){
    int a = 0;
    char str;
    int flag_sent = 1;
    int flag_txt = 1;
    int sent_count = 0;
    int char_count = 0;
    int string_length = 1000;
    while (1)
    {
        char_count = 0;
        (*txt) = realloc((*txt), sizeof(char*) * (sent_count+1));
        if ((*txt) == NULL){
                        puts("Недостаточно памяти!");
                        exit(0);
                }
        (*txt)[sent_count] = malloc(sizeof(char) * string_length);
        str = getchar();
        if (str == '\n')
        {
            a++;
            if (a==2)
                break;
        }
        else{
                (*txt)[sent_count][char_count] = str;
                a=0;
        }

        do
        {
            char_count++;
            str = getchar();
            if ((str == '\n')){
                a++;
                break;
            }
            else{
                a = 0;
            }
            (*txt)[sent_count][char_count] = str;
            flag_sent = (strchr(sen_sep,str) == NULL);
            if (char_count>=string_length - 2)
            {
                string_length = string_length + 500;
                (*txt)[sent_count] = (char*) realloc((*txt)[sent_count], string_length);
                if ((*txt)[sent_count] == NULL){
                        puts("Недостаточно памяти!");
                        exit(0);
                }
            }
        }
        while(flag_sent == 1);
        if (a == 2)
            break;
        str=getchar();
        if (str == '\n')
                a++;
        else
                a = 0;
        (*txt)[sent_count][char_count+1] = ' ';
        (*txt)[sent_count][char_count+2] = '\0';
        sent_count++;
    }
    return sent_count;
}
int error_check(int new_sent_count, char** txt,int f){
        int d,m,y,i,n;
        f = 0;
        for(i = 0 ; i<new_sent_count ; i++){
                n = i+1;
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        if(d<0 || m<0 || y<0){
                                f = 1;
                                puts("Значение года, месяца или дня не могут быть отрицательными. \n");
                                printf("Ошибка в предложении номер %d. \n",n);
                                break;
                        }
                        if(m == 0 || m > 12){
                                f = 1;
                                puts("Колличество месяцев не может быть больше 12 или равнять 0. \n");
                                printf("Ошибка в предложении номер %d. \n",n);
                                break;
                        }
                        if(d == 0 || d > 31){
                                f = 1;
                                puts("Колличество дней в месяце не может превышать 31. \n");
                                printf("Ошибка в предложении номер %d. \n",n);
                                break;
                        }
                        if(d > 30 && (m!= 3 || m!=5 || m!=8 || m!=10)){
                                f = 1;
                                puts("Колличество дней в Апреле, Июле, Сентябре, Ноябре ровняется 30. \n");
                                printf("Ошибка в предложении номер %d. \n",n);
                                break;
                        }
                        if(d == 29 && m == 3 && ((y%4>=0) && ((y%100>=0) && (y%400>=0)) && (y%100==0))){
                                f = 1;
                                puts("Колличество дней в феврале зависит от того,високосный ли год. \n");
                                printf("%d год не является високосным. \n",y);
                                printf("Ошибка в предложении номер %d. \n",n);
                                break;
                        }
                        if(d>29 && m == 3){
                                f = 1;
                                puts("Колличество дней в феврале не может быть больше 29. \n");
                                printf("Ошибка в предложении номер %d. \n",n);
                                break;
                        }
                }
        }
        return f;
}
int delete_sent(int sent_count, char*** txt){
    for(int i = 0; i<sent_count; i++){

            int j = i+1;

            while (j<sent_count){
                if (strcasecmp((*txt)[i],(*txt)[j])==0){

                    free((*txt)[j]);
                    sent_count--;
                    for (int k = j; k<=sent_count;k++){
                        (*txt)[k] = (*txt)[k+1];
                    }
                }
                else{
                    j++;
                }
            }
    }
    return sent_count;
}
void print_sentenses_with_curent_date(int new_sent_count, char** txt){
        time_t t = time(NULL);
        struct tm* timeinfo = localtime(&t);
        int d,m,y,f,i;
        for(i = 0 ; i<new_sent_count ; i++){
                f = 0;
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        if(y == timeinfo->tm_year+1900  &&  m == timeinfo->tm_mon+1){
                          f = 1;
                          break;
                        }
                }
                if(f) printf("%s\n",txt[i]);
        }
}

int delete_sentenses_of_19th_century(int new_sent_count, char** txt){
        int d,m,y,f,i,j,count;
        char* t = " ";
        for(i = 0 ; i < new_sent_count;i++){
                count = 1;
                for(j = 0; j < strlen(txt[i]);j++){
                        if (strcasecmp(t,&txt[i][j]) == 0){
                        count++;
                        }
                }
                f = 0;
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        if(y < 1900 && y > 1800){
                          f++;
                        }
                }
                if(f == count){
                        free(txt[i]);
                        new_sent_count--;
                }
        }
        return(new_sent_count);
}
void print_soon_and_late_date(int new_sent_count, char** txt){
        int d,y,m,i,j;
        int min,max;
        for(i = 0 ; i<new_sent_count ; i++){
                min = 1000000000;
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        int value = y*10000 + m*100 + d;
                        if(value<min){
                                min = value;
                        }
                }
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        int value = y*10000 + m*100 + d;
                        if(value == min){
                                printf("%d/%d/%d ",d,m,y);
                                break;
                        }
                }
                max = 0;
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        int value = y*10000 + m*100 + d;
                        if(value>max){
                                max = value;
                        }
                }
                for(char* p = txt[i]; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                        int value = y*10000 + m*100 + d;
                        if(value = max){
                                printf("%d/%d/%d\n",d,m,y);
                                break;
                        }
                }

        }
}
void sort_sentenses(int new_sent_count,char*** txt){
        qsort(*txt,new_sent_count,sizeof(char*),cmp);
}
int cmp(const void* a,const void* b){
        int d,m,y,i;
        int min1,min2;
        char **s1 = (char**) a;
        char **s2 = (char**) b;
        min1 = 1000000000;
        min2 = 1000000000;
        for(char* p = *s1; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                int value = y*10000 + m*100 + d;
                if(value<min1){
                        min1=value;
                }
        }
        for(char* p = *s2; sscanf(p, "%d/%d/%d", &d, &m, &y) > 0 ; p += 11){
                int value = y*10000 + m*100 + d;
                if(value<min1){
                        min2=value;
                }
        }
        if(min1>min2){
                return 1;
        }
        if(min2>min1){
                return -1;
        }
        if(min1=min2){
                return 0;
        }
}

void free_txt(int new_sent_count, char*** txt){
        for (int i =0;i<new_sent_count;i++)
        free((*txt)[i]);
    free(*txt);
}
void print(char** txt, int new_sent_count){
        char** s;

        for (s = txt; s < txt+new_sent_count; s++)
                printf("%s", *s);
        printf("\n");
}
