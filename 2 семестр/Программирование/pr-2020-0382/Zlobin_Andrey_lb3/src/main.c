#include <stdio.h>
#include <stdlib.h>

int get_sentence(char ** received_sentence)
{
	int sent_size=1;
	char c;
	char *sentence = *received_sentence;
	do
	{
		c = getchar();
		if (c!=' ' && c!='\t' && c!='\n')
		{
			sent_size=1;
			sentence=malloc(sent_size*sizeof(char));
			*(sentence + sent_size - 1)=c;
			while (c!='.' && c!=';' && c!='?' && c!='!')
			{
				c = getchar();
				if (c!='\t' && c!='\n')
				{
					sent_size+=1;
					sentence = realloc(sentence, sent_size*sizeof(char));
					*(sentence+sent_size - 1)=c;
				}

			}
			sentence = realloc(sentence, (sent_size+1)*sizeof(char));
			*(sentence + sent_size)='\0';
		}
	}while (c!='.' && c!=';' && c!='?' && c!='!');
	*received_sentence = sentence;
	return sent_size-1;
}

int get_text(char*** text)
{
	int size_sentence = 0;
	int size_text=0;
	char **sent=*text;
	sent=malloc((size_text+1)*sizeof(char*));
	do
	{
		
			size_sentence = get_sentence(&sent[size_text]);
			size_text = size_text + 1;
			sent=realloc(sent,(size_text + 1)*sizeof(char*));
		
		*text=sent;
	}while (*(sent[size_text-1]+size_sentence)!='!');
	return size_text;
}

int edit_text(char** text, int size)
{
	int i=0;
	int j=0;
	int changed_size=size;
	for (i=0; i<size; i++)
	{
		for (j=0; text[i][j]!='\0'; j++)
		{
			if (text[i][j]=='7')
			{
				changed_size--;
				text[i][0]='\0';
				break;
			}
		}
	}
	return changed_size;
}

int main()
{
	char **text;
	int size;
	int edited_size;
	int i;
	size = get_text(&text);
	edited_size = edit_text(text, size);
	for (i=0; i<size; i++)
	{
		if (text[i][0]!='\0')
		{
			printf("%s\n", text[i]);
		}
	}
	printf("%s %d %s %d\n", "Количество предложений до", size-1, "и количество предложений после", edited_size-1);
	for (int j=0;j<size;j++)
	{
		free(text[j]);
	}
	free(text);
	return 0;
}
