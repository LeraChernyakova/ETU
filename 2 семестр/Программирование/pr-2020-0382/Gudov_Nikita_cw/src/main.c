#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define TEXTSIZE 10
#define SENTSIZE 50
#define TRUE 1
#define FALSE 0


char* get_sentence()
{
    int ssize=SENTSIZE;
    char* sentence=malloc(ssize*sizeof(char));
    char symbol;
    int i=0;
    while(TRUE)
    {
        symbol=getchar();
        sentence[i++]=symbol;
        if (i==ssize)
        {
            ssize+=20;
            sentence=(realloc(sentence, ssize*sizeof(char)));
        }
        if (symbol=='.') break;
    }
    sentence[i]='\0';
    return sentence;
}

char** get_text(int* size)
{
    int tsize=TEXTSIZE;
    char** text=malloc(TEXTSIZE*sizeof(char*));
    char* sentence;
    int i=0;
    while(TRUE)
    {
        sentence=get_sentence();
        text[i++]=sentence;
        if(getchar() == '\n') break;
        if(i==tsize)
        {
            tsize+=5;
            text=realloc(text, tsize*sizeof(char*));
        }
    }
    *size=i;
    return text;
}

char** HiddenAgent(char** text, int* size)
{
    int c=0;
    char** text2=malloc(*size*sizeof(char*));
    for(int i=0; i<*size; i++)
    {

        char* p=strstr(text[i],"HiddenAgent");
        if ((p != &text[i][0]) && (p !=NULL))
        {
            text2[c++]=text[i];
        }
    }
    *size=c;
    return text2;
}

char** Remover(char** text, int* size)
{
    int c=0;
    int trigger, d;
    char** text2=malloc(*size*sizeof(char*));
    for(int i=0; i< *size; i++)
    {
        d=0;
        for(int j=0; j<i; j++)
        {
            if(strlen(text[i])==strlen(text[j]))
            {
                trigger=1;
                for(int k=0; k<strlen(text[i]); k++)
                {
                    if(tolower(text[j][k])!=tolower(text[i][k]))
                    {
                        trigger=0;
                        break;
                    }

                }
                d+=trigger;
            }
        }
        if(d==0)
        {
            text2[c++]=text[i];
        }
    }
    *size=c;
    return text2;
}

char** FLalpha(char** text, int* size)
{
    for (int i =0; i< *size; i++)
    {
        int c=0;
        int l=strlen(text[i])-1;
        for (int j=0; j<(l/2); j++)
        {
            if(tolower(text[i][j])==tolower(text[i][l-j-1]))
            {
                c+=1;
            }
            else break;
        }
        int k;
        for(k=0; k<l-2*c; k++)
        {
            text[i][k]=text[i][k+c];
        }
        text[i][k]='.';
        text[i][k+1]='\0';
    }
    return text;
}

int isPalindrom(char* str)
{
    int i=0, j=strlen(str)-1;
    while (i<j)
    {
        if(str[i++]!=str[j--])
        {
            return FALSE;
        }
    }
    return TRUE;
}

char** Palindrom(char** text, int* size)
{
    int c=0;
    char** text2=malloc(*size*sizeof(char*));
    char* sep=" .,";
    for (int i =0; i< *size; i++)
    {
        int trigger=1;
        char *word = strtok(text[i], sep);
        while(word != NULL)
        {
            char* pstext=text[i];
            if (isPalindrom(pstext))
            {
                trigger=0;
                break;
            }
            word=strtok(NULL, sep);
        }
        if (trigger==1)
        {
            text2[c++]=text[i];
        }
    }
    *size=c;
    return text2;
}

int sortstr(const void *a, const void *b)
{
    char** x=(char**)a;
    char** y=(char**)b;
    return strcmp(*x, *y);
}

char** Sort(char** text, int* size)
{
    char** text2=malloc(*size*sizeof(char*));
    char *arr[*size];
    int i;
    for (i = 0; i < *size; i++)
    {
        arr[i] = (char*) malloc(25);
    }
    char* sep=" .,";
    for (int i =0; i< *size; i++)
    {
        int j=0;
        char *word = strtok(text[i], sep);
        while (word != NULL)
        {
            arr[j++]=word;
            word = strtok(NULL, sep);
        }
        qsort(arr, j, sizeof(char*), sortstr);
        for (int k=0; k<j; k++)
        {
            printf("%s",arr[k]);
            if (k==j-1){printf(". ");}
            else{printf(" ");}
        }
    }
    return text2;
}

void menu(int sw, char*** text, int size, char** (*f)(char**, int*))
{
    wprintf(L"%d:\n",sw);
    wprintf(L"----------------------------------------------------------------------------------------\n");
    char** text2 = f(*text, &size);
    for(int i = 0; i < size; i++)
        {
            printf("%s ", text2[i]);
            free(text2[i]);
        }
    for(int i = 0; i < size; i++) free((*text)[i]);
    free(text2); free(*text);
}


int main() {
    setlocale(LC_ALL, "");
    wprintf(L"Введите текст, используя только латинские буквы и цифры: ");

    int size;
    char **text;

    text = get_text(&size);
    char **tmp = Remover(text, &size);
    free(text);
    text = tmp;
    wprintf(L"\n\nПовторения были удалены: ");
    for (int i = 0; i < size; i++) printf("%s ", text[i]);
    printf("\n");
    char **temp = text;

    wprintf(L"\n\t\t\t\t\tДля продолжения выберите номер доступной команды:\n");
    wprintf(L"\t1: Удалить все символы в начале и конце строки так, чтобы в итоге первый и последний символ были различными (без учета регистра). Например, строка “abcdba” должна принять вида “cd”.\n");
    wprintf(L"\t2: Отсортировать все слова в предложении в лексикографическом порядке.\n");
    wprintf(L"\t3: Удалить все предложения, в которых хотя бы одного слово является палиндромом.\n");
    wprintf(L"\t4: Вывести все предложения в которых есть слово “HiddenAgent” и которое не является первым словом.\n");
    wprintf(L"\t5: Выход.\n\n");


    int sw;
    scanf("%d", &sw);
    switch (sw)
        {

            case 1: menu(1, &temp, size, FLalpha); getch(); break;
            case 2: wprintf(L"%d\n",sw); Sort(temp, &size); getch(); break;
            case 3: menu(3, &temp, size, Palindrom); getch(); break;
            case 4: menu(4, &temp, size, HiddenAgent); getch(); break;
            case 5: wprintf(L"Exit\n"); getch(); break;
            default: wprintf(L"Выберите что-нибудь из предложенного списка!!\n"); getch(); break;

        }
        return 0;
    }
