#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


char** readtext(int *pN){
        char **text;
        char *word;
        int countword=0;
        int countsymbol=0;
        char symbol;
        int i;
        int j;
	int flag=0;
        int *size=NULL;
        text=NULL;
	printf("Введите текст\n");
        do{
                word=NULL;
                size=realloc(size,(countword+1)*sizeof(int));
                text=realloc(text,(countword+1)*sizeof(char*));
		if (size==NULL || text==NULL){
			printf("Память не выделена\n");
			return NULL;
		}
                countsymbol=0;
                do{
                        scanf("%c",&symbol);
                        word=realloc(word,(countsymbol+1)*sizeof(char));
			if (word==NULL){
				printf("Память не выделена\n");
				return NULL;
			}
                        countsymbol++;
                        word[countsymbol-1]=symbol;
                }while (symbol!='.' && symbol!='\n');
                if (symbol=='\n'){
                        break;
                }
                word=realloc(word,(countsymbol+1)*sizeof(char));
		if (word==NULL){
                                printf("Память не выделена\n");
                                return NULL;
                        }
                word[countsymbol]='\0';
                if (countword!=0){
                        for (i=0;i<countword;i+=1){
				flag=1;
				if (size[i]==strlen(word)){
					for (j=0;j<size[i];j++){
						if ((int)text[i][j]!=(int)word[j]){
							if ((int)word[j]>64 && (int)word[j]<123 && (int)text[i][j]>64 && (int)text[i][j]<123){
                                                               if (abs((int)word[j]-(int)text[i][j])!=32){
								       flag=0;
							       }
							}
							else{
								flag=0;
							}
						}
					}
				}
				else{
					flag=0;
				}
			       if (flag==1){
				       break;
			       }	       
			}

                }
                if (flag==0 || countword==0){
                        text[countword]=word;
                        size[countword]=strlen(word);
                        countword+=1;
                }
        }while (word[countsymbol-1]!='\n');
        *pN=countword;
        return text;
}


char** replace(char** text, int count){
	int i;
	int j;
	char *str="AaIiOoUuEeYy";
	for (i=0;i<count;i++){
		for (j=0;j<strlen(text[i]);j++){
			if(strrchr(str,text[i][j])){
				text[i][j]=(char)((int)text[i][j]+1);
			}	
		}
	}
	return text;
}


char** substring(char **text, int count,int *psub){
	char **substr=NULL;
	int i;
	int j;
	int g=0;
	char *str1="To ";
	char *str2=" or not to ";
	for (i=0;i<count;i++){
		if (strstr(text[i],str1) && strstr(text[i],str2)){
			int v1=3;
			int v2=strstr(text[i],str2)-text[i]+11;
			int len1=strstr(text[i],str2)-text[i]-3;
			int len2=strlen(text[i])-(v2+1);
			int k=0;
			if (len1>len2){
				k=v1;
				int h=strlen(text[i])+len1;
				substr=realloc(substr,(g+1)*sizeof(char*));
				if (substr==NULL){
					printf("Память не выделена\n");
					return NULL;
				}
				for (j=0;j<len1;j++){
					substr[g]=realloc(substr[g],(k-2)*sizeof(char));
					if (substr[g]==NULL){
						printf("Память не выделена\n");
						return NULL;
					}
					substr[g][j]=text[i][k];
					k++;
				}
				substr[g]=realloc(substr[g],(k-2)*sizeof(char));
				if (substr[g]==NULL){
                                        printf("Память не выделена\n");
                                	return NULL;
				}
				substr[g][j+1]='\0';
			}
			else{
				k=v2;
                                int h=strlen(text[i])+len2;
                                substr=realloc(substr,(g+1)*sizeof(char*));
                                if (substr==NULL){
                                        printf("Память не выделена\n");
                                        return NULL;
                                }
                                for (j=0;j<len2;j++){
                                        substr[g]=realloc(substr[g],(k-2)*sizeof(char));
                                        if (substr[g]==NULL){
                                                printf("Память не выделена\n");
                                                return NULL;
                                        }
                                        substr[g][j]=text[i][k];
                                        k++;
                                }
                                substr[g]=realloc(substr[g],(k-2)*sizeof(char));
                                if (substr[g]==NULL){
                                        printf("Память не выделена\n");
                                        return NULL;
                                }
                                substr[g][j+1]='\0';
			}
			g++;
		}
	}
	*psub=g;
	return substr;
}


char** delete(char** text,int *pN){
	int i;
	int j;
	int len;
	int *index=NULL;
	int k=0;
	for (i=0;i<*pN;i++){
		len=0;
		for (j=0;j<strlen(text[i]);j++){
			if (text[i][j]!=' ' && text[i][j]!='.'){
				len++;
			}
			else{
				break;
			}
		}
		if (len==4){
			index=realloc(index,(k+1)*sizeof(int));
			if (index==NULL){
                                printf("Память не выделена\n");
                                return NULL;
                        }
			index[k]=i-k;
			k++;
		}
	}
	for (i=0;i<k;i++){
		for (j=index[i];j<(*pN-1);j++)
			text[j]=text[j+1];
		free(text[*pN]);
		*pN-=1;
	}
	return text;
}


void write(char **text,int N){
	for (int i=0;i<N;i++)
		printf("%s",text[i]);
	printf("\n");
}


int sort(const void*a,const void*b){
	char *str1=*(char**)a;
	char *str2=*(char**)b;
	return (int)str1[strlen(str1)-2]-(int)str2[strlen(str2)-2];
}


void writesub(char **substr,int countsub){
	for (int i=0;i<countsub;i++)
		printf("%s\n",substr[i]);
}
int main(){
        int i;
        char **text;
        int *pN;
        int N=0;
	int fun=1;
	char **substr=NULL;
	int *psub;
	int countsub;
	psub=&countsub;
        pN=&N;
        text=readtext(pN);
	while (fun){
		printf("Введите необходимый номер подпункта. Введите 0 для выхода из программы\n");
		scanf("%d",&fun);
		switch(fun){
			case 1:
				text=replace(text,N);
				write(text,N);
				break;
			case 2:
				substr=substring(text,N,psub);
				write(text,N);
				if (substr!=NULL){
                                        writesub(substr,countsub);
                                }
				break;
			case 3:
				text=delete(text,pN);
				write(text,N);
				break;
			case 4:
				qsort(text,N,sizeof(char*),sort);
				write(text,N);
				break;
			default:
				break;
		}
	}
        for (i=0;i<N;i++)
                free(text[i]);
        free(text);
        return 0;
}

