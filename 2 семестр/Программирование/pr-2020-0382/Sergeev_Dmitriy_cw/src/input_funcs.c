#include "input_funcs.h"

Sentence get_sentence()
{
    Sentence ret_sent;
    ret_sent.sent=malloc(1*sizeof(wchar_t));
    wchar_t c='u';
    wscanf(L"%lc",&c);
    if (c!=L'\t' && c!=L'.' && c!=L' ')
    {
        if (c=='\n')
        {
            ret_sent.sent[0]=c;
            return ret_sent;
        }
        int size=0;
        ret_sent.sent[size]=c;
        while (c!=L'.')
        {
            wscanf(L"%lc",&c);
            size+=1;
            ret_sent.sent=realloc(ret_sent.sent,(size+1)*sizeof(wchar_t));
            ret_sent.sent[size]=c;
        }
        ret_sent.sent=realloc(ret_sent.sent,(size+2)*sizeof(wchar_t));
        ret_sent.sent[size+1]=L'\0';
    }
    else
    {
        ret_sent.sent[0]=L'\0';
        return ret_sent;
    }
    return ret_sent;
}

Text get_Text()
{
    Text MyText;
    Sentence MySentence;
    MyText.text_size=0;
    MyText.doc=malloc((MyText.text_size+1)*(sizeof(Sentence *)*2));
    while (1)
    {
        MySentence = get_sentence();
        if (MySentence.sent[0]!='\0' && MySentence.sent[0]!='\n')
        {
            MyText.doc[MyText.text_size] = MySentence;
            MyText.text_size += 1;
            MyText.doc = realloc(MyText.doc, (MyText.text_size + 1) * (sizeof(Sentence *)*2));
        }
        else
        {
            if (MySentence.sent[0]=='\n')
            {
                free (MySentence.sent);
                return MyText;
            }
        }
    }
}
