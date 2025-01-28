#include "text_changing.h"

Text shift_text(Text test_text,int count, int* del)
{
    int point=0;
    for (int i=0;i<count;i++)
    {
        for (int j=del[point];j<test_text.text_size-1;j++)
        {
            test_text.doc[j]=test_text.doc[j+1];
        }
        point++;
        del[point]-=point;
        test_text.text_size-=1;
        test_text.doc=realloc(test_text.doc,(test_text.text_size+1)*sizeof(Sentence*)*2);
    }
    free(del);
    return test_text;
}

Text DoSentencesUnique(Text FixText)
{
    for (int i=0;i<FixText.text_size;i++)
    {
        int* need_to_delete=calloc(FixText.text_size,sizeof(int));
        int count=0;
        for (int j=i+1;j<FixText.text_size;j++)
        {
            int flag=1;
            if ((wcsncasecmp(FixText.doc[i].sent,FixText.doc[j].sent,wcslen(FixText.doc[i].sent))))
            {
                flag=0;
            }
            if (flag==1)
            {
                need_to_delete[count]=j;
                count++;
            }
        }
        FixText=shift_text(FixText,count,need_to_delete);
    }
    return FixText;
}

int upsortcmp(const void* a, const void* b)
{
    int i=0;
    Sentence* aa=(Sentence*)a;
    Sentence* bb=(Sentence*)b;
    long int suma=0,sumb=0;
    while (aa->sent[i]!=L' ' && aa->sent[i]!=L'.' && aa->sent[i]!=L',')
    {
        suma+=aa->sent[i++];
    }
    i=0;
    while (bb->sent[i]!=L' ' && bb->sent[i]!=L'.' && bb->sent[i]!=L',')
    {
        sumb+=bb->sent[i++];
    }
    return suma-sumb;
}

Text UpSort(Text SortText)
{
    qsort(SortText.doc,SortText.text_size,sizeof(Sentence),upsortcmp);
    return SortText;
}

Sentence Shift_Sent(Sentence sc,int* beg,int count,int shift_size, wchar_t sym)
{
    int accumulate=0;
    for (int i=0;i<count;i++)
    {
        accumulate+=shift_size;
        for (int k=0;k<shift_size;k++)
        {
            sc.sent=realloc(sc.sent,(wcslen(sc.sent)+2)*(sizeof(wchar_t)));
            int nach=wcslen(sc.sent);
            for (int j = nach; j > beg[i]; j--)
            {
                sc.sent[j]=sc.sent[j-1];
            }
            sc.sent[nach+1]='\0';
        }
        if (sym==L'%%')
        {
            sc.sent[beg[i]]=L'<'; sc.sent[beg[i]+1]=L'p'; sc.sent[beg[i]+2]=L'e'; sc.sent[beg[i]+3]=L'r'; sc.sent[beg[i]+4]=L'c'; sc.sent[beg[i]+5]=L'e'; sc.sent[beg[i]+6]=L'n'; sc.sent[beg[i]+7]=L't'; sc.sent[beg[i]+8]=L'>';
        }
        if (sym==L'#')
        {
            sc.sent[beg[i]]=L'<'; sc.sent[beg[i]+1]=L'р'; sc.sent[beg[i]+2]=L'е'; sc.sent[beg[i]+3]=L'ш'; sc.sent[beg[i]+4]=L'е'; sc.sent[beg[i]+5]=L'т'; sc.sent[beg[i]+6]=L'к'; sc.sent[beg[i]+7]=L'а'; sc.sent[beg[i]+8]=L'>';
        }
        if (sym==L'@')
        {
            sc.sent[beg[i]]=L'('; sc.sent[beg[i]+1]=L'a'; sc.sent[beg[i]+2]=L't'; sc.sent[beg[i]+3]=L')';
        }
        beg[i+1]+=accumulate;
    }
    return sc;
}

Text ChangeSpecSym(Text RedText)
{
    for (int i=0;i<RedText.text_size;i++)
    {
        int* id_perc=calloc(wcslen(RedText.doc[i].sent),sizeof(int));
        int* id_resh=calloc(wcslen(RedText.doc[i].sent),sizeof(int));
        int* id_at=calloc(wcslen(RedText.doc[i].sent),sizeof(int));
        int count_perc=0;
        int count_resh=0;
        int count_at=0;
        for (int j=0;j<wcslen(RedText.doc[i].sent);j++)
        {
            if (RedText.doc[i].sent[j]==L'%%')
            {
                id_perc[count_perc]=j;
                count_perc++;
            }
        }
        RedText.doc[i]=Shift_Sent(RedText.doc[i], id_perc, count_perc,8,L'%%');
        for (int j=0;j<wcslen(RedText.doc[i].sent);j++)
        {
            if (RedText.doc[i].sent[j]==L'#')
            {
                id_resh[count_resh]=j;
                count_resh++;
            }
        }
        RedText.doc[i]=Shift_Sent(RedText.doc[i], id_resh, count_resh,8,L'#');
        for (int j=0;j<wcslen(RedText.doc[i].sent);j++)
        {
            if (RedText.doc[i].sent[j]==L'@')
            {
                id_at[count_at]=j;
                count_at++;
            }
        }
        RedText.doc[i]=Shift_Sent(RedText.doc[i], id_at, count_at,3,L'@');
        free(id_at);
        free(id_perc);
        free(id_resh);
    }
    return RedText;
}

Text Delete_3_consonant_in_a_row(Text RedactText)
{
    wchar_t Lat_con[]=L"BCDFGHJKLMNPQRSTVWXYZ";
    wchar_t Rus_con[]=L"БВГДЖЗЙКЛМНПРСТФХЦЧШЩ";
    int* need_to_delete=calloc(1,sizeof(int));
    int count=0;
    for (int i=0;i<RedactText.text_size;i++)
    {
        int flag=0;
        int j=-1;
        wchar_t* beg=wcsstr(RedactText.doc[i].sent,L".");
        while (*(beg+j)!=' ' && (beg+j)!=RedactText.doc[i].sent)
        {
            j--;
        }
        int k;
        if ((beg+j)==RedactText.doc[i].sent)
        {
            k=0;
        }
        else
        {
            k = 1;
        }
        while (*(beg+j+k)!='.' && flag==0)
        {
            if (wcschr(Lat_con,towupper(*(beg+j+k)))!=0 || wcschr(Rus_con,towupper(*(beg+j+k)))!=0)
            {
                if (wcschr(Lat_con,towupper(*(beg+j+k+1)))!=0 || wcschr(Rus_con,towupper(*(beg+j+k+1)))!=0)
                {
                    if (wcschr(Lat_con,towupper(*(beg+j+k+2)))!=0 || wcschr(Rus_con,towupper(*(beg+j+k+2)))!=0)
                    {
                        flag=1;
                        need_to_delete[count]=i;
                        count++;
                        need_to_delete=realloc(need_to_delete,(count+1)*sizeof(int));
                    }
                }
            }
            k++;
        }
    }
    RedactText=shift_text(RedactText,count,need_to_delete);
    return RedactText;
}
