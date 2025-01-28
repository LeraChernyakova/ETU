#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

char* inpsent()
{
    int sentsize = 100;
    int sentlenght = 0;
    int sym;

    char *sentence = malloc(sentsize*sizeof(char));

    while (TRUE)
    {
        sym = getchar();
        sentence[sentlenght++] = sym;
        if (sym == '.' || sym == ';' || sym == '?' || sym == '!') break;
        if (sentlenght == sentsize)
        {
            sentsize += 100;
            sentence = realloc(sentence, sentsize);
        }
    }
    if (sentlenght == sentsize)
    {
        sentsize += 1;
    }
    sentence[sentlenght] = '\0';
    return sentence;
}

char* space_c(char* sent)
{
    int i = 0;
    while(sent[i] == ' ' || sent[i] == '\t' || sent[i] == '\n')
    {
        int j;
        for (j = 0; j < strlen(sent) - 1; j ++)
        {
            sent[j] = sent[j+1];
        }

        sent[j] = '\0';
    }
    return sent;
}

int no_seven (char* sent)
{

    int ans = 1;
    for (int i = 0; i < strlen(sent)-1; i ++)
    {
        if (sent[i]=='7')
        {
            ans = FALSE;
        }
    }
    return ans;
}

int main()
{
    int text_len = 0;
    int wrongcount = 0;
    char* end_sent = "Dragon flew away!";

    int text_mem_size = 100;
    char** text = malloc(text_mem_size*sizeof(char*));

    char* sentence;

    while (TRUE)
    {
        sentence = inpsent();
        sentence = space_c(sentence);

        if (no_seven(sentence))
        {
            text[text_len++] = sentence;
        }
        else wrongcount += 1;

        if (text_len == text_mem_size)
        {
            text_mem_size += 100;
            text = realloc(text, text_mem_size*sizeof(char*));
        }

        if (!strcmp(sentence, end_sent)) break;
    }

    for (int i = 0; i < text_len; i++)
    {
        if (text[i][0]!='\0')
        {
            printf("%s\n", text[i]);
        }

    }
    for (int i = 0; i < text_len; i++)
    {
        free(text[i]);
    }
    free(text);

    printf("Количество предложений до %d и количество предложений после %d\n", text_len+wrongcount-1, text_len-1);
    return 0;
}