#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define size 5
#define endStr "Dragon flew away!"


char **enterTextArr(){
    char **textArr= malloc(size * sizeof(char*));
    char symb;
    int nStr= 0;


    do{
        textArr= realloc(textArr, (nStr + 1) * sizeof(char*));
        textArr[nStr]= malloc(size * sizeof(char));
        
        int nSymb= 0;
        
        scanf(" ");
        do{
            scanf("%c", &symb);
            textArr[nStr]= realloc(textArr[nStr], (nSymb + 1) * sizeof(char));
            textArr[nStr][nSymb]= symb;
            nSymb+= 1;
        } while((symb != '.') && (symb != ';') && (symb != '?') && (symb != '!'));
        
        textArr[nStr]= realloc (textArr[nStr], (nSymb + 1) * sizeof(char));
        textArr[nStr][nSymb]= '\0';
        nStr+= 1;
    } while(strcmp(textArr[nStr-1], endStr) != 0);
    
    return textArr;
}

int nStrFirst(char **textArr){
    int nStr= 0;

    while (strcmp(textArr[nStr], endStr) != 0){
        nStr+=1;
    }
    
    return nStr;
}

char **editTextArr(char **textArr, int nStrFirst){
    int nStr= 0;
    int k= 0;
    
    while ( nStr != nStrFirst){
        for (int i= 0; i < strlen(textArr[nStr]); i++ ){
            if (textArr[nStr][i]== '7'){
                k+= 1;
            }
        }

        if (k > 0){
            free (textArr[nStr]);
            for (int i= nStr ; i < nStrFirst - 1; i++)
                textArr[i]= textArr[i+1];
        } else{
           nStr+= 1; 
        }
        k= 0;
    }
    
    return textArr;
}

int main(){
    char **textArr= enterTextArr();
    
    int nFirst= nStrFirst(textArr);
    textArr= editTextArr(textArr, nFirst+1);
    
    int nLast= nStrFirst(textArr);
    
    for(int i= 0; i < nLast; i++)
        printf("%s\n", textArr[i]);
    
    printf ("%s\n", endStr);
    printf("Количество предложений до %d и количество предложений после %d\n", nFirst, nLast);

    for(int i= 0; i < nLast+1; i++){
        free(textArr[i]);
    }
    
    free(textArr);
    return 0;
}