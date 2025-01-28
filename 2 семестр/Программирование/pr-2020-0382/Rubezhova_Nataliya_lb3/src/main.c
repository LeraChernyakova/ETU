#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE_ARR 10
#define BUFFER 50
int delete_sent(char* sent){
    int i=0, state=1;
    int ind_start=0,ind_end=0;//индексы начала и конца слова
    while(i<strlen(sent)-1){
        while(*(sent+i)!=' '&&*(sent+i)!='.'&&*(sent+i)!=';'&&*(sent+i)!='?'&&*(sent+i)!='!')i++;
        if(*(sent+i)==' '){
                if(*(sent+i-1)!=',')ind_end=i-1;
                else ind_end=i-2;
        }
        else ind_end=i-1;
        int j,check_dgt=0,check_alpha=0;
        for(j=ind_start+1;j<ind_end;j++){
            if(isdigit(*(sent+j))&&ind_start!=ind_end)check_dgt++;
            if(isalpha(*(sent+j))&&ind_start!=ind_end)check_alpha++;
        }
        if(check_dgt>0&&check_alpha>0) return 0;
        if(check_dgt>0&&check_alpha==0){
            if(isalpha(*(sent+ind_start))==1||isalpha(*(sent+ind_end))==1)
                return 0;
        }
        if(i!=strlen(sent)-1){
            ind_start=i+1;
            i++;
        }
    }
    return 1;
}

int main()
{
    int size_arr=SIZE_ARR;
    int buffer=BUFFER;
    char c;
    int length;
    int count_0=0,count_1=0;
    char** text=malloc(size_arr*sizeof(char*));
    int flag=1,i;
    while(flag==1){
        length=0;
        c=getchar();
        if(c=='\n'||c==' '||c=='\t') c=getchar();
        if(c=='\n'||c=='\t')c=getchar();
        char* buf=calloc(buffer,sizeof(char));
        while(c!='.'&&c!=';'&&c!='?'&&c!='!'){
            buf[length++]=c;
            if(length==buffer){
                buffer*=2;
                buf=realloc(buf,buffer);
            }
            c=getchar();
        }
        buf[length]=c;
        buf[length+1]='\0';
        text[count_0]=buf;
        if(strcmp(buf,"Dragon flew away!\0")==0)
            flag=0;
        count_0++;
        if(count_0==size_arr){
            size_arr*=2;
            text=realloc(text, size_arr*sizeof(char*));
        }
    }
    for(i=0;i<count_0;i++){
        if(delete_sent(text[i])){
                printf("%s\n", text[i]);
                count_1++;
        }
    }
    for(i=0;i<count_0;i++)free(text[i]);
    free(text);
    count_0-=1;
    count_1-=1;
    printf("Количество предложений до %d и количество предложений после %d\n",count_0,count_1);
    return 0;

}
