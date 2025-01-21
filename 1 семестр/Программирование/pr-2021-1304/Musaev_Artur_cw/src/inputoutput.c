#include "inputoutput.h"


struct Text readText()
{
	int i,m,n;
	wchar_t c;
	struct Text text;
	setlocale(LC_ALL, "");
	m=0;
	text.sents=malloc(sizeof(struct Sentence*));
	c=getwchar();
	while (c!='\n'){
		n=0;
		text.sents=realloc(text.sents,(m+2)*sizeof(struct Sentence));
		text.sents[m]=malloc(sizeof(struct Sentence));
		text.sents[m]->str=malloc(sizeof(wchar_t));
		while ((c!='.') && (c!='!') && (c!='?')){
			text.sents[m]->str=realloc(text.sents[m]->str,sizeof(wchar_t)*(n+2));
			text.sents[m]->str[n]=c;
			text.sents[m]->str[n+1]='\0';
			n++;
			c=getwchar();
		}
		text.sents[m]->str=realloc(text.sents[m]->str,sizeof(wchar_t)*(n+2));
		text.sents[m]->str[n]=c;
		text.sents[m]->str[n+1]='\0';
		text.sents[m]->size=n+1;
		c=getwchar();
		c=getwchar();
		m++;
	}
	text.size=m;
	return text;


}


void output(struct Text* text)
{
	int i;  
	for(i=0;i<text->size;i++){
		wprintf(L"%ls ",text->sents[i]->str,text->sents[i]->size);
	}
	wprintf(L"\n");
}

