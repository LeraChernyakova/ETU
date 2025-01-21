#include "func.h"

struct Text read(){
	struct Text tex;
	struct Sentence s;	
	int m,n,counter,i,d,q;
	d=1;
	wchar_t c;
	tex.t=malloc(sizeof(wchar_t*));
	n=0;
	m=0;	
	while (d == 1){		
		tex.t=realloc(tex.t,sizeof(wchar_t*)*(n+2));
		tex.t[n]=malloc(sizeof(wchar_t)*2);				
		c=getwchar();				
		if (c == '\n'){
			d=0;
		} else {
		tex.t[n][0]=c;
		tex.t[n][1]='\0';
		counter=0;
		q=0;
		while ((c!='.') ){			
			counter= counter +1;			
			tex.t[n]=realloc(tex.t[n],sizeof(wchar_t)*(counter+2));
			c=getwchar();						
			tex.t[n][counter]=c;
			tex.t[n][counter+1]='\0';
		}		
		}
		s.s=tex.t[n];								
		n=n+1;
		
	}		
tex.size =n;
return tex;

}


void choice(){
fputws(L"1 - Для каждого предложения вывести строку-дату вида “ДД-ММ-ГГГГ”, где день - количество слов в предложении, месяц - наибольшая длина слова в предложении, год - общее количество символов в предложении + 1900.\n",stdout);
           fputws(L"2 - Вывести предложения так, чтобы слова шли в обратном порядке.\n",stdout);
           fputws(L"3 - Отсортировать предложения по длине первого слова в предложении.\n",stdout);
           fputws(L"4 - Удалить все предложения у которых все слова имеют длину не больше 3 символов.\n",stdout);
           fputws(L"5 - Выход из программы.\n",stdout); 

}


