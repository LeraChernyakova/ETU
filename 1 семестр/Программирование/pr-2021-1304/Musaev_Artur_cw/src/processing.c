#include "processing.h"

void delete_lat_and_kir(struct Text * text)
{
	int y,i,j,k,u,maxim,flag1,flag2;
	setlocale(LC_ALL, "Rus");
	wchar_t alp[33]=L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	flag1=0;
	flag2=0;
	k=0;
	maxim=-1;
	for(i=0;i<text->size;i++){
		for(j=0;j<text->sents[i]->size;j++){
			if ((text->sents[i]->str[j]==L' ') || (text->sents[i]->str[j]==L',') || (text->sents[i]->str[j]==L'?') || (text->sents[i]->str[j]==L'!')){
				k=0;
			}
			else{
				k++;
				if (k>maxim){
					maxim=k;
				}
			}
		}
	}	
	wchar_t word[maxim+1];
 
	for(i=0;i<text->size;i++){
		k=0;
		flag1=0;
		flag2=0;
		for(j=0;j<text->sents[i]->size;j++){
			if ((text->sents[i]->str[j]==L' ') || (text->sents[i]->str[j]==L',') || (text->sents[i]->str[j]==L'?') || (text->sents[i]->str[j]==L'!') || (text->sents[i]->str[j]==L'.')){
				k=0;
				flag1=0;
				flag2=0;
				for(u=0;u<wcslen(word);u++){
					if ((97<=word[u]) && (word[u]<=122)){
						flag1=1;
					}
					else{
						for(y=0;y<wcslen(alp);y++){
							if (alp[y]==word[u]){
								flag2=1;
							}
						}
					}
				}
				if ((flag1) && (flag2)){
				free(text->sents[i]);
				memmove(&text->sents[i],&text->sents[i+1],(text->size-i)*sizeof(struct Sentence*));
				text->size--;
				i--;
				break;
		}
			}
			else{
				word[k]=towlower(text->sents[i]->str[j]);
				word[k+1]=L'\0';
				k++;
			}
		}
	}
}


int funcmp( const void * val1, const void * val2 )
{
	struct Sentence** first = (struct Sentence**) val1;
	struct Sentence** second = (struct Sentence**) val2;
	int i,counter1,counter2;
	counter1=0;
	counter2=0;

	for(i=0;i<first[0]->size;i++){
		if (((65<=first[0]->str[i]) && (first[0]->str[i]<=90)) || ((97<=first[0]->str[i]) && (first[0]->str[i]<=122))){
			counter1++; 
		}
	}
	for(i=0;i<second[0]->size;i++){
		if (((65<=second[0]->str[i]) && (second[0]->str[i]<=90)) || ((97<=second[0]->str[i]) && (second[0]->str[i]<=122))){
			counter2++; 
		}
	}
	return counter2-counter1;

}

void replace(struct Text *text)
{	
 
	setlocale(LC_ALL, "");
	wchar_t change[]=L">special symbol<";
	int i,maxim,j,k,temp;
	maxim=-1;
	for(i=0;i<text->size;i++){
		if (text->sents[i]->size>maxim){
			maxim=text->sents[i]->size;
		}
	}
	temp=maxim*wcslen(change);
	wchar_t a[text->size+1][temp];
	int length[text->size];
	for(i=0;i<text->size;i++){
		for(j=0;(text->sents[i]->str[j]!='\0');j++){
			a[i][j]=text->sents[i]->str[j];
		}
		a[i][j]='\0';
	}
	for(i=0;i<text->size;i++){
		j=0;
		temp=wcslen(a[i]);
		while(a[i][j]!='\0'){
			if ((a[i][j]==L',') || (a[i][j]==L'.') || (a[i][j]==L';') ||(isspace(a[i][j]))){
				wmemmove(&a[i][j+wcslen(change)],&a[i][j+1 ],temp-j);
				for(k=j;k<j+wcslen(change);k++){
					a[i][k]=change[k-j];
				}
				j=j+wcslen(change)-1;
				temp+=wcslen(change)-1;
			}
			j++;
		}
		length[i]=temp;
	}
	for(i=0;i<text->size;i++){
		free(text->sents[i]->str);
	}
 
	for(i=0;i<text->size;i++){
		text->sents[i]->str=malloc(sizeof(wchar_t)*(wcslen(a[i])+2));
	}	
	for(i=0;i<text->size;i++){
		wcscpy(text->sents[i]->str,a[i]);
		text->sents[i]->size=length[i];
	}
}
 
 
 
void palindroms(struct Text* text)
{	
 
	int i,j,k,u,maxim,flag1,flag2,flag_find;
	setlocale(LC_ALL, "");
	flag1=0;
	flag2=0;
	k=0;
	maxim=-1;
	for(i=0;i<text->size;i++){
		for(j=0;j<text->sents[i]->size;j++){
			if ((text->sents[i]->str[j]==L' ') || (text->sents[i]->str[j]==L',') || (text->sents[i]->str[j]==L'?') || (text->sents[i]->str[j]==L'!')){
				k=0;
			}
			else{
				k++;
				if (k>maxim){
					maxim=k;
				}
			}
		}
	}	
	wchar_t word[maxim+1];
 
	for(i=0;i<text->size;i++){
		k=0;
		flag1=0;
		flag2=0;
		for(j=0;j<text->sents[i]->size;j++){
			if ((text->sents[i]->str[j]==L' ') || (text->sents[i]->str[j]==L',') || (text->sents[i]->str[j]==L'?') || (text->sents[i]->str[j]==L'!') || (text->sents[i]->str[j]==L'.')){
				k=0;
				flag_find=1;
				for(u=0;u<wcslen(word)/2;u++){
					if (word[u]!=word[wcslen(word)-u-1]){
						flag_find=0;
					}
				}
				if (flag_find){
					flag1=1;
				}
				else{
					flag2=1;
				}
			}
			else{
				word[k]=towlower(text->sents[i]->str[j]);
				word[k+1]=L'\0';
				k++;
			}
		}
		if ((flag1==1) && (flag2==0)){
			wprintf(L"%ls\n",text->sents[i]->str);
			wprintf(L"Палиндромы на месте!\n");
		}
		else if (flag1==0){
			wprintf(L"%ls\n",text->sents[i]->str);
			wprintf(L"Кто-то потерял все палиндромы.\n");
		}
		else{
			wprintf(L"%ls\n",text->sents[i]->str);
			wprintf(L"Чего-то не хватает.\n");
		}
		wprintf(L"\n");
	}
}
 
 
 
 
void remove_repetes(struct Text* text){
	setlocale(LC_ALL,"");
	int i,j,temp;
	for(i=0;i<text->size;i++){
		j=i+1;
		while(j<text->size){
			if (!wcscasecmp(text->sents[i]->str,text->sents[j]->str)){
				//text->sents[j]->size=-1;
				//wcscpy(a[j],L"\0");
				//wprintf(L"%ls\n",text->sents[j]->str);
				free(text->sents[j]);
				memmove(&text->sents[j],&text->sents[j+1],(text->size-j)*sizeof(struct Sentence*));
				text->size--;
				j--;
			}
			j++;
		}
	}
}

