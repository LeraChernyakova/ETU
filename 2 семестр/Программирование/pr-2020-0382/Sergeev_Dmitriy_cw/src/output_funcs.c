#include "output_funcs.h"

void time(Text TimeText)
{
    long int sum=0;
    for (int i=0;i<TimeText.text_size;i++)
    {
        wchar_t** replace=calloc(1,sizeof(wchar_t*));
        wchar_t* beg;
        int count=1;
        while (wcsstr(TimeText.doc[i].sent,L" sec ")!=0)
        {
            wchar_t* digit=calloc(1,sizeof(wchar_t));
            replace=realloc(replace,count*sizeof(wchar_t*));
            replace[count-1]=wcsstr(TimeText.doc[i].sent,L" sec ");
            count++;
            int j=-1;
            beg=wcsstr(TimeText.doc[i].sent,L" sec ");
            while (*(beg+j)!=' ' && (beg+j+1)!=TimeText.doc[i].sent)
            {
                j--;
            }
            int k=1;
            while (*(beg+j+k)!=' ')
            {
                digit=realloc(digit,(k+1)*sizeof(wchar_t));
                digit[k-1]=*(beg+j+k);
                k++;
            }
            digit=realloc(digit,(k+1)*sizeof(wchar_t));
            digit[k-1]='\0';
            sum=sum+wcstol(digit,NULL,10);
            *beg='1';
            free(digit);
        }
        for (int u=0;u<count-1;u++)
        {
            *(replace[u])=' ';
        }
        free(replace);
    }
    wprintf(L"%d min %d sec\n", sum/60, sum-(sum/60)*60);
}

void text_output(Text MyText)
{
for (int i = 0; i < MyText.text_size; i++) 
	{
        	wprintf(L"%ls\n", MyText.doc[i].sent);
        }
        wprintf(L"\n");
}

