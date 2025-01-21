#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 5
#define end_sent "Dragon flew away!"

char** readText(){
    int sent_cnt = 0;
	char **txt = malloc(size * sizeof(char*));
	char symb;
	do{
	    txt = realloc(txt, (sent_cnt + 1) * sizeof(char*));
	    txt[sent_cnt] = malloc(size * sizeof(char));
	    int symb_cnt = 0;
	    scanf (" ");
	    do{
			scanf("%c", &symb);
			txt[sent_cnt] = realloc(txt[sent_cnt], (symb_cnt + 1) * sizeof(char));
            txt[sent_cnt][symb_cnt] = symb;
            symb_cnt += 1;
	    }while((symb != ';') && (symb != '.') && (symb != '!') && (symb != '?'));
	    txt[sent_cnt] = realloc(txt[sent_cnt], (symb_cnt + 1) * sizeof(char));
        txt[sent_cnt][symb_cnt] = '\0';
        sent_cnt += 1;
	}while(strcmp(txt[sent_cnt-1], end_sent) != 0);
	return txt;
}

int countSent(char **txt){
    int cnt_bef = 0;
    while (strcmp(txt[cnt_bef], end_sent) != 0){
        cnt_bef+=1;
    }
    return cnt_bef;
}

char **rightText(char **txt, int sent_bef){
    int sent_aft = 0;
    while ( sent_aft != sent_bef){
        int seven = 0;
        for (int i = 0; i < strlen(txt[sent_aft]); i++ ){
            if (txt[sent_aft][i] == '7')
                seven += 1;
        }
        if (seven > 0){
            free (txt[sent_aft]);
            for (int i = sent_aft ; i < sent_bef - 1; i++)
                txt[i] = txt[i+1];
        }
        else
            sent_aft += 1;
    }
    return txt;
}

void freeText(char** txt,  int cnt_bef){
    for(int i = 0; i < cnt_bef; i++)
        free(txt[i]);
    free(txt);
}

int main(){
    char **text = readText();
    int count_before = countSent(text);
    text = rightText(text, count_before+1);
    int count_after = countSent(text);
    for(int i = 0; i < count_after; i++)
        printf("%s\n", text[i]);
    printf ("%s\n", end_sent);
    printf("Количество предложений до %d и количество предложений после %d\n", count_before, count_after);
    freeText(text, count_after+1);
    return 0;
}

