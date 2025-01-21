#include "define.h"
#include "inp_out_free.h"
#include "processing.h"

struct Text Del_Repeat(struct Text text,int j){
	free(text.t[j]);
	for(int i=j; i<text.len-1;i++){
		text.t[i]=text.t[i+1];
	}
	text.len--;
return text;
}
struct Text If_Del(struct Text text){
	int i =0;
	int j=0;
	int t_len=text.len;
	while(i< (text.len)-1){
		j =i+1;

		while (j<text.len){
			if (wcscasecmp(text.t[i]->s,text.t[j]->s)==0){
				text=Del_Repeat(text,j);

			}
			else{
				j++;
			}
		}
		i++;
	}

	return text;
}

struct Word Find_Word(wchar_t* sent, int begin)
{
	int size = STAND_WORD;
	wchar_t* buf;
	buf = malloc(size*sizeof(wchar_t*));
	if(buf){
        struct Word word;
        //word.w = malloc(size*sizeof(wchar_t*));
        word.w=buf;
        int i = begin+1;
        word.begin = begin+1;
        while(sent[i]!=' '&&sent[i]!=','&&sent[i]!='.')
        {
            i++;
        }

        word.end = i;
        wchar_t t;
        t = sent[i];
        sent[i] = '\0';
        wcscpy(word.w, &sent[word.begin]);
        sent[i] = t;
        return word;
    }
    else{
        struct Word er_word;
        wprintf(L"Ошибка при работе функции. Память выделена некорректтно. Пожалуйста, завершите программу");
        return er_word;
    }
}
void Colour_Words(struct Text text){
	for(int i=0;i<text.len;i++){
		int begin=-1;
		int j=0;
		while(j<wcslen(text.t[i]->s)-1){
			//int size = STAND_WORD;
			struct Word word;
			word = Find_Word(text.t[i]->s,begin);
			begin=word.end;
			j=begin;
			if((word.end-word.begin)%4==0){
				wprintf(L"\033[31m%ls",word.w);
			}
			if((word.end-word.begin)%4==1){
				wprintf(L"\033[34m%ls",word.w);
			}
			if((word.end-word.begin)%4==2){
				wprintf(L"\033[32m%ls",word.w);
			}
			if((word.end-word.begin)%4==3){
				wprintf(L"\033[33m%ls",word.w);
			}
			wprintf(L"\033[0m%lc",text.t[i]->s[j]);
			free(word.w);
			}

		}
	wprintf(L"\n");
	}
int If_Number(struct Word word){
	int f=1;
	for(int i=0;i<word.end-word.begin;i++){
        if (iswdigit(word.w[i])){
            f=1;
        }
        else{
            f=0;
            break;
        }
    }
	return f;
}
struct Text Del_Digit(struct Text text){
	for(int i=0;i<text.len;i++){
		int j=-1;
		int len = wcslen(text.t[i]->s);
		while(j<len-1){
			struct Word word;
			word = Find_Word(text.t[i]->s,j);
			if(If_Number(word)){
				wcscpy(&text.t[i]->s[word.begin],&text.t[i]->s[word.end+1]);
				len =wcslen(text.t[i]->s);
				if (j==len-1){
					text.t[i]->s[j+1]='\0';
					text.t[i]->s[j]='.';
					len =wcslen(text.t[i]->s);
				}
				continue;
			}

			j=word.end;
			free(word.w);
		}

	}



	return text;
}

int Len_Last_Word (struct Sentence sent){
	int size = STAND_WORD;
	int len_last_word = 0;
	int j=-1;
	int len = wcslen(sent.s);
	struct Word word;
	while(j<len-1){
		word.w = malloc(size*sizeof(wchar_t*));;
		word = Find_Word(sent.s,j);
		j=word.end;
		if(j<len-1){
			free(word.w);
			}
		}
	len_last_word= word.end - word.begin;
	free(word.w);
return len_last_word;
}

int cmp(const void* a,const void* b){
	struct Sentence* sent_1= *((struct Sentence**)a);
	struct Sentence* sent_2= *((struct Sentence**)b);
	int len_1=Len_Last_Word(*sent_1);
	int len_2=Len_Last_Word(*sent_2);
	if (len_1<len_2)
		return -1;
	if (len_1>len_2)
		return 1;
	return 0;
}
void Upp_Words(struct Text text){
    	for(int i=0;i<text.len;i++){	
		int j=-1;
		int len = wcslen(text.t[i]->s);
		struct Word word;
		while(j<len-1){
			word = Find_Word(text.t[i]->s,j);	
            		if (iswupper(word.w[0]) && iswupper(word.w[wcslen(word.w)-1])){        
                		wprintf(L"%ls: %d\n",word.w,i+1);
            		}
            			j=word.end;
            			free(word.w);         			
        	}
    	}   
}

