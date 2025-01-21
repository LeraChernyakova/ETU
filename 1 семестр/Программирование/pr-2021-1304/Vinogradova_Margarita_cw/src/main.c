#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "text_processing.h"
#define STEP 5


struct Sentence{
    wchar_t *words;
    int size;
    int len;


};
struct Sentence* readSentence(){
    int size=STEP;

    wchar_t *buf = malloc(size* sizeof(wchar_t));
    wchar_t temp;
    int n=0;
    do{
        if(n<=size-2){
            wchar_t *t= realloc(buf,size+STEP);
            if(!t){puts("ERROR: закончилась память");}
            size+=STEP;
            buf=t;
            //printf("new size=%d\n",size);

        }
        temp=getwchar();
        buf[n]=temp;
        n++;
    }while(temp!='.' && temp!='\n');
    buf[n]='\0';
    struct Sentence *sentence= malloc(sizeof (struct Sentence));
    sentence->words=buf;
    sentence->size=size;
    sentence->len=n-1;

    return sentence;
}

struct Text{
    struct Sentence **sentences;
    int size;
    int n;
};

struct Text readText(){
    int size=STEP;
    struct Sentence** txt= malloc(size*sizeof(struct Sentence));
    int n=0;
    struct Sentence *temp;
    int null_kol=0;
    do{
        temp=readSentence();
        if(temp->words[0]=='\n'){
            null_kol++;
            free(temp->words);
            free(temp);
        }else{
            null_kol=0;
            txt[n]=temp;
            n++;
        }
    } while (null_kol<1);

    struct Text full_text;
    full_text.size=size;
    full_text.sentences=txt;
    full_text.n=n;

    return full_text;

}

struct Arr{
    int kol_repeat;
    wchar_t* word;
    int len_rep;
};

    struct Mask{
    wchar_t *masks;
};



int main() {

    setlocale(LC_ALL,"");

    struct Text new_text = readText();
    new_text = del_rep(new_text);

    for(int i=0;i<new_text.n;i++){
//        wprintf(L"\nstring---->  %d : %ls %d %d\n",i,new_text.sentences[i]->words,new_text.sentences[i]->len,new_text.n);
    }



    ///////////////////////////////////////////////////////////////////////////////////

    int k=1;
while(k){
    int operation;
    printf("\n\nДля получения маски по каждому предложению введите 1.\nЧтобы удалить все предложения, в которых нет заглавных букв в начале слова введите 2."
           "\nЧтобы отсортировать слова в предложении по количеству гласных букв в слове введите 3."
           "\nЧтобы для каждого предложения получить количество одинаковых слов в строке введите 4."
           "\nЧтобы завершить программу введите 5.\n--->");
    scanf("%d",&operation);
    switch (operation) {
        case 1:{
            struct Mask *mask=task1(new_text);
            for(int i=0;i<new_text.n;i++){
                wprintf(L"%d: mask= %ls\n",i,mask[i].masks);
                }

            free(mask);
            }
            break;
        case 2:{
            new_text= task2(new_text);
            for(int i=0;i<new_text.n;i++){
                wprintf(L"%ls",new_text.sentences[i]->words);
            }
            puts("");
        }
            break;
        case 3:{

            new_text= task3(new_text);
            for(int i=0;i<new_text.n;i++){
                wprintf(L"%ls",new_text.sentences[i]->words);
            }
            puts("");
        }
            break;
        case 4:{
            struct Arr **arr= task4(new_text);

            for(int i=0;i<new_text.n;i++){
                int len=arr[i][0].len_rep;
                //printf("%d",len);
                for(int z=0;z<len;z++){
                    //printf("s ");
                    wprintf(L"'%ls':%d; ",arr[i][z].word,arr[i][z].kol_repeat);
                }
                puts("");



            }
            for(int f=0;f<new_text.n;f++){
                free(arr[f]);
            }
            free(arr);

        }
            break;
        case 5:{
            k=0;
        }break;
        default:
            puts("");


    }
}




    for(int i=0;i<new_text.n;i++){
        free(new_text.sentences[i]->words);
    }
    for(int i=0;i<new_text.n;i++){
        free(new_text.sentences[i]);
    }







    ///////////////////////////////////////////////////////////////////////////////////////


    return 0;
}

