#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getSentence(char* lastSymbol){
    short sentenceSize = 50;
    char* sentence = calloc(sentenceSize, sizeof(char));

    char sym;
    do sym = getchar(); while (sym == ' ' || sym == '\t' || sym == '\n');

    short count = 0;
    short endOfSentence = 0;
    while(!endOfSentence){
        if(count == sentenceSize){
            sentenceSize += 15;
            sentence = realloc(sentence, sentenceSize * sizeof(char));
        }

        sentence[count++] = sym;
        if(sym == '.' || sym == ';' || sym == '?' || sym == '!') endOfSentence = 1;
        else sym = getchar();
    }

    *lastSymbol = sym;
    sentence[count] = '\0';
    return sentence;
}

int main()
{
    const char* terminationString = "Dragon flew away!";
    short n = 0, m = 0;
    short textSize = 20;
    char** text = calloc(textSize, sizeof(char*));

    short endOfText = 0;
    while(!endOfText){
        char lastSym;
        char* sentence = getSentence(&lastSym);

        switch (lastSym){
            case '?':
                n++;
                break;
            case '.':
            case ';':
                n++;
                text[m++] = sentence;
                if(m == textSize){
                    textSize += 10;
                    text = realloc(text, textSize * sizeof(char*));
                }
                break;
            case '!':
                if(!strcmp(sentence, terminationString)) {
                    text[m] = sentence;
                    endOfText = 1;
                }
                break;
        }
    }

    for(int i = 0; i < m+1; i++){
        puts(text[i]);
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d", n, m);
    return 0;
}
