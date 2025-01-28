#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELTA 100

int deleting_ent_tab_escp(char* text){
    //Удаление всех переносов строки в тексте
    
    for (int i = 0; i < strlen(text); i ++)
    {
        if (text[i] == '\n')
            text[i] = ' ';
    }
    
    //Удаление табуляций. Каждое предложение печатается с новой строки. Удаление лишних пробелов.
    
    int n = 0;
    if ((text[0] == '\t') || (text[0] == ' '))
        for (int i = 0; i < strlen(text); i ++)
            text[i] = text[i + 1];
    for (int i = 0; i < strlen(text); i ++)
    {
        if ((text[i] == '.') || (text[i] == ';') || (text[i] == '?'))
        {   
            text[i + 1] = '\n';
            if (text[i + 2] == ' ')
                for (int k = i + 2; k < strlen(text); k ++)
                    text[k] = text[k + 1];
            n ++;
        }
        if ((text[i + 1] == ' ') && (text[i] == ' '))
            for (int k = i + 2; k < strlen(text); k ++)
                    text[k] = text[k + 1];
    }
    return n;
}

int deleting_numb(char* text){
    
    // Удаление предложений с цифрами внутри слов
    int start_indx = 0, end_indx = 0;
    int m = 0;
    for (int i = 0; i < strlen(text); i ++){
        if (text[i] == '\n'){
            end_indx = i - 1;
            int flag1 = 0, flag2 = 0;
            for (int k = start_indx; k <= end_indx; k ++)
            {
                if (isdigit(text[k]))
                {
                    if ((k != start_indx) && (k != end_indx - 1))
                        if ((text[k - 1] != ' ') && (!isdigit(text[k - 1])))
                            flag1 = 1;
                }
                if (isdigit(text[k]))
                {
                    if ((k != start_indx) && (k != end_indx - 1))
                        if ((text[k + 1] != ' ') && (!isdigit(text[k + 1])) && (flag1 == 1))
                            flag2 = 1;
                }
            }
            if (flag2 && flag1){
                for (int t = start_indx; t < strlen(text); t ++)
                    text [t] = text[t + (end_indx - start_indx + 1) + 1];
                i = start_indx;
                m ++;
            }
            else
                start_indx = i + 1;
        }
    }
    return m;
}


int main()
{
    int flag = 0, i = 0, size = 100;
    char c;
    char* text = (char*)calloc(size, sizeof(char));
    
    // Считывается текст в динамический буфер
    
    while (!flag){
        size = size + DELTA;
        char* check = (char*)realloc(text, size);
        if (check)
            text = check;
        while ((i < size) && (!flag)){
            c = getchar();
            text [i] = c;
            i ++;
            if (c == '!')
                flag = 1;
        }
    }
    
    int n = deleting_ent_tab_escp(text);
    int m = n - deleting_numb(text);
    
    printf("%s\n", text);
    printf("Количество предложений до %d и количество предложений после %d\n", n, m);
    
    free(text);
    return 0;
}  
