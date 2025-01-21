#include "decide.h"
struct text removeSentense(struct text t)
{int k=0,j=0;
for (int i=0;i<t.kol_sen;i++)
{	j=i+1;
	while (j<t.kol_sen)
		{wchar_t *str1=t.sen[i]->str;
		wchar_t *str2=t.sen[j]->str;
		if (!wcscasecmp(str1,str2))
			{free(t.sen[j]->word);
                	free(t.sen[j]->str);
			free(t.sen[j]);
			for (int k=j;k<t.kol_sen-1;k++)
                                t.sen[k]=t.sen[k+1];
                        t.kol_sen--;}
		else
			j++;}}
return t;}

void free_for_two(wchar_t **s,int size)
	{for (int i=0;i<size;i++)
		free(s[i]);
	free(s);}
	
int mask_fun(wchar_t *str,int kol,wchar_t *mask,int size)
{	int i=0,j=0,k=0;
	if ((size!=kol && !wcschr(mask,(wchar_t)'*')) || size>kol+1)
		return 0;
	while (j<size)
		if (mask[j]!='*' && mask[j]!='?' && str[i]!=mask[j])
			return 0;
		else
			{if (mask[j]=='*')
				{j++;
				i=kol-size+j;//Синхронизировали элементы j и i(kol-(size-j))
				}
				
			 else
				{i++;
				j++;}
			}
		
	return 1;}
	
int strtok_for_mask(struct text Text,wchar_t *mask,int size)
{	for (int i=0;i<Text.kol_sen;i++)
	{	Text.sen[i]->str;
		wchar_t *token;
		wchar_t *temp=malloc(sizeof(wchar_t)*(Text.sen[i]->kol+1));
		if (!temp)
			return 0;
		wcscpy(temp,Text.sen[i]->str);
		wchar_t *t=wcstok(temp,L" ,.",&token);
		int j=0;
		while (t)
			{if (mask_fun(t,Text.sen[i]->word[j],mask,size))
				printf("%ls ",t);
			t=wcstok(NULL,L" ,.",&token);
			j++;}
		free(temp);
	}
	return 1;
}
					
			


int cmp(const void *a,const void *b){
	struct sentense **first=(struct sentense **) a;
	struct sentense **second=(struct sentense **) b;
	int n1=(*first)->kol_word;
	int n2=(*second)->kol_word;
	int sum1=(*first)->kol-(*first)->kol_word,sum2=(*second)->kol-(*second)->kol_word;
	float sr1=(float)sum1/n1, sr2=(float) sum2/n2;
	if (sr1>sr2)
		return 1;
	else
		if (sr1<sr2)
			return -1;
	return 0;
	 
}

int cmp_1(const void *a,const void *b){
	wchar_t **first=(wchar_t**) a;
	wchar_t **second=(wchar_t**) b;
	int n1=wcslen(*first),n2=wcslen(*second);
	if (n1>n2)
		return -1;
	else
		if (n1==n2)
			return 0;
	return 1;}
int cmp_2(const void *a,const void *b)
{	int *first=(int*) a;
	int *second=(int*) b;
	if (*first>*second)
		return -1;
	else
		if (*first==*second)
			return 0;
	return 1;}		
		
wchar_t * qsort_for_3(struct sentense sen)
{wchar_t *token;
wchar_t *t=wcstok(sen.str,L" ,.",&token);
wchar_t **temp=malloc(sizeof(wchar_t *)*(sen.kol_word));
if (!temp)
	return NULL;
int i=0,sum=0;
while (i<sen.kol_word)
	{temp[i]=malloc(sizeof(wchar_t)*(sen.word[i]+1));
	if (!temp[i])
		return NULL;
	wcscpy(temp[i],t);
	t=wcstok(NULL,L" ,.",&token);
	i++;}
qsort(temp,sen.kol_word,sizeof(wchar_t *),cmp_1);
qsort(sen.word,sen.kol_word,sizeof(int),cmp_2);
wchar_t *res=malloc(sizeof(wchar_t)*(sen.kol+1));
if (!res)
	return NULL;
for (int j=0;j<sen.kol_word;j++)
	{wcsncpy(res+sum,temp[j],(sen.word[j]));
	sum+=sen.word[j]+1;
	res[sum-1]=' ';
	}
res[sum-1]='.';
res[sum]='\0';
free_for_two(temp,sen.kol_word);
return res;}

struct text del_sentense(struct text t)
{	int i=0;	
	while (i<t.kol_sen)
	{	if (t.sen[i]->kol_word>5 || t.sen[i]->kol_word<2)
			{free(t.sen[i]->word);
                	free(t.sen[i]->str);
			free(t.sen[i]);
			for (int j=i;j<t.kol_sen-1;j++)
				t.sen[j]=t.sen[j+1];
			t.kol_sen--;}
		else
			i++;
	}
return t;}
		
void free_for_text(struct text t)
{	for(int i=0;i<t.kol_sen;i++)
	{	free(t.sen[i]->word);
		free(t.sen[i]->str);
	}
	free(t.sen);
}
