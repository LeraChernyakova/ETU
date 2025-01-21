#include "print_and_input.h"
int * strtok_for_you(struct sentense *sen)
{wchar_t *token;
wchar_t *t=wcstok(sen->str,L" ,.",&token);
while (t)
	t=wcstok(NULL,L" ,.",&token);
int *temp=malloc(sizeof(int)*Size);
if (!temp)
	return NULL;
t=sen->str;
int k=0,j=0,size=Size;
for (int i=0;i<sen->kol;i++)
{	if (!t[i])
		{temp[k]=j;
		k++;
		if (k>=size)
		{	int *temp1=realloc(temp,sizeof(int)*(size+Size));
			if (!temp1)
				{free(temp);
				return NULL;}
			size+=Size;
			temp=temp1;}
		j=0;}
	else
		j++;}
sen->kol_word=k;
return temp;}	
		
						
	

struct sentense* readsen()
{	int size=Size;
	wchar_t *temp=malloc(sizeof(wchar_t)*size);
	if (!temp)
		return NULL;
	int i=0;
	wchar_t c;
	do{
		c=fgetwc(stdin);
		if (i>=size-2)
			{wchar_t *t=realloc(temp,sizeof(wchar_t)*(size+Size));
			if (!t)
				{free(temp);
				return NULL;}
			size+=Size;
			temp=t;
			}
		temp[i]=c;
		i++;}
	while  (c!='.' && c!='\n');
	temp[i]='\0';
	struct sentense *Sen=malloc(sizeof(struct sentense));
	if (!Sen)
		return NULL;
	Sen->str=temp;
	Sen->kol=i;
	wchar_t *temp1=malloc(sizeof(wchar_t)*size);
	if (!temp1)
		return NULL;
	wcscpy(temp1,temp);
	Sen->word=strtok_for_you(Sen);
	if (!Sen->word)
		return NULL;
	Sen->str=temp1;
	free(temp);
	return Sen;
}

struct text readtext()
{	struct text Text;	
	struct sentense  **text=malloc(sizeof(struct sentense*)*Size);
	if (!(text))
		{Text.kol_sym=-1;
		return Text;}
	int size=Size,i=0,count=0,n=0;
	struct sentense *temp;
	do{	if (size<=i+2)
			{struct sentense  **t=realloc(text,sizeof(struct sentense*)*(size+Size));
			if (!t)
				{for(int k=0;k<i;k++)
					free(text[i]);
				free(text);
				Text.kol_sym=-1;
				return Text;}
			size+=Size;
			text=t;}
		temp=readsen();
		if (!temp)
			{for(int k=0;k<i;k++)
					free(text[i]);
				free(text);
			Text.kol_sym=-1;
			return Text;}
		if (temp->str[0]=='\n')
			count++;
		else
			{count=0;
			 text[i]=temp;
			n+=temp->kol;
			i++;};
	}
	while (count!=2);
	scanf(" ");
	Text.sen=text;
	Text.kol_sen=i;
	Text.kol_sym=n;
	return Text;
}
	

void printText(struct text t)
{	for(int i=0;i<t.kol_sen;i++)
		if (wcscmp(t.sen[i]->str,(wchar_t*)"\n"))
			printf("%ls\n",t.sen[i]->str);
}
