#include <stdio.h>
#include <stdlib.h>

int text(char*** s, int** len)
{
	char c;
	int i=0;
	int* l=*len;
	l=malloc(1*sizeof(int));
	char **sent=*s;
	sent=malloc((i+1)*sizeof(char*));
	while (c!='!')
	{
		scanf("%c",&c);
		if (c!=' ' && c!='\t' && c!='\n')
		{
			int number=0;
			int sent_size=1;
			sent[i]=malloc(sent_size*sizeof(char));
			*(sent[i]+number)=c;
			while (c!='.' && c!=';' && c!='?' && c!='!')
			{
				scanf("%c",&c);
				if (c!='\t' && c!='\n')
				{
					sent_size+=1;
					number=number+1;
					sent[i]=realloc(sent[i],sent_size*sizeof(char));
					*(sent[i]+number)=c;
				}
			
			}
			sent[i]=realloc(sent[i],(sent_size+1)*sizeof(char));
			*(sent[i]+number+1)='\0';
			*(l+i)=sent_size;
			i=i+1;
			sent=realloc(sent,(i+1)*sizeof(char*));
			l=realloc(l,(i+1)*sizeof(int));
		}
		*len=l;
		*s=sent;
	}
	return i;
}

int delete_wrong_sentences(char** s,int* len, int i)
{
	int count=i;
	for (int t=0;t<i;t++)
	{
		for (int z=0;z<len[t];z++)
		{
			if (s[t][z]=='7')
			{
				count--;
				s[t][0]='\0';
				break;
			}
		}
	}
	return count;
}

int main()
{
	int *len;
	char **s;
	int i=text(&s,&len);
	int count=delete_wrong_sentences(s,len,i);
	for (int t=0;t<i;t++)
	{
		if (s[t][0]!='\0')
		{
			printf("%s\n", s[t]);
		}
	}
	printf("%s", "Количество предложений до ");
	printf("%d", i-1);
	printf("%s", " и количество предложений после ");
	printf("%d\n", count-1);
	for (int j=0;j<i;j++)
	{
		free(s[j]);
	}
	free(s);
	return 0;
}