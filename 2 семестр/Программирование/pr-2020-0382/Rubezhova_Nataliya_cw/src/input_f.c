#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "structs.h"
#include "input_f.h"

wchar_t get_Word(wchar_t c,Word* word_ptr) {
    wchar_t* tm;
    int size_buf=SIZE;
    wchar_t* buffer=(wchar_t*)calloc(size_buf,sizeof(wchar_t));
    int leng_w=0;
    if(c==' '||c==',')c=getwchar();
    while(c!=' '&&c!=','&&c!='.'){
        buffer[leng_w++]=c;
        if(leng_w==size_buf){
            size_buf*=2;
            tm=realloc(buffer,size_buf*sizeof(wchar_t));
            buffer=tm;
        }
        c=getwchar();
    }
    buffer[leng_w++]=c;
    buffer[leng_w]='\0';
    word_ptr->leng_word=leng_w;
    word_ptr->buf=(wchar_t*)malloc((leng_w+1)*sizeof(wchar_t));
    wcscpy(word_ptr->buf,buffer);
    free(buffer);
    return c;
}
wchar_t get_Sent(wchar_t sym, Sentence* sent_ptr){
    Word* tm;
    int count_words=SIZE;
    Word* buf_words_demo=(Word*)calloc(count_words,sizeof(Word));
    int leng_s=0;
    while(sym!='.'){
        sym=get_Word(sym,&buf_words_demo[leng_s++]);
        if(leng_s==count_words){
            count_words*=2;
            tm=realloc(buf_words_demo,count_words*sizeof(Word));
            buf_words_demo=tm;
        }
    }
    sent_ptr->leng_sent=leng_s;
    sent_ptr->buf_words=(Word*)malloc((leng_s+1)*sizeof(Word));
    int i;
    for(i=0;i<leng_s;i++){
        sent_ptr->buf_words[i]=buf_words_demo[i];
    }
    free(buf_words_demo);
    sym=getwchar();
    return sym;
}
void get_Text(wchar_t c, Text* inp_p){
    Sentence* tm;
    int count_sent=SIZE;
    Sentence* buf_sents_demo=(Sentence*)malloc(count_sent*sizeof(Sentence));
    int leng_t=0;
    if(c=='\n') c=getwchar();
    while(c!='\n'){
        c=get_Sent(c,&buf_sents_demo[leng_t++]);
        if(leng_t==count_sent){
            count_sent*=2;
            tm=realloc(buf_sents_demo,count_sent*sizeof(Sentence));
            buf_sents_demo=tm;
        }
        if(c=='\n')c=getwchar();
    }
    inp_p->leng_text=leng_t;
    int i;
    inp_p->buf_sents=(Sentence*)malloc((leng_t+1)*sizeof(Sentence));
    for(i=0;i<leng_t;i++){
        inp_p->buf_sents[i]=buf_sents_demo[i];
    }
    free(buf_sents_demo);

}
void get_str_sent(Text* text_p){
    int i,j;
    for(i=0;i<text_p->leng_text;i++){
        int size=1;
        wchar_t* str=(wchar_t*)calloc(size,sizeof(wchar_t));
        for(j=0;j<text_p->buf_sents[i].leng_sent;j++){
            int size_add=text_p->buf_sents[i].buf_words[j].leng_word;
            str=realloc(str,(size+size_add)*sizeof(wchar_t));
            wcscat(str,text_p->buf_sents[i].buf_words[j].buf);
            size+=size_add;
        }
        text_p->buf_sents[i].str_sent=(wchar_t*)malloc(size*sizeof(wchar_t));
        wcscpy(text_p->buf_sents[i].str_sent,str);
        text_p->buf_sents[i].leng_str=size;
        free(str);
    }
}
void check_repeat(Text* text_p,Sentence* sent_p){
    int i,j,k=0,flag;
    for(i=0;i<text_p->leng_text;i++){
        if(wcscasecmp(sent_p->str_sent,text_p->buf_sents[i].str_sent)==0){
            flag=1;
            k++;
        }
        else
            flag=0;
        if(k>1&&flag==1){
            for(j=i;j<text_p->leng_text-1;j++){
                text_p->buf_sents[j]=text_p->buf_sents[j+1];
            }
            text_p->leng_text-=1;
        }
    }
}



