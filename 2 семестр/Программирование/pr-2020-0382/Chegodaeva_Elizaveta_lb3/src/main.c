#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* get_text(){
    int length = 0;
    char sym = 0;
    char *text = malloc(1*sizeof(char));
    sym = getchar();
    if(sym!=' ' && sym!='\t'){
        text[length] = sym;
        length++;
    }
    while (sym != '.' && sym != ';' && sym != '?' && sym != '!'){
        sym = getchar();
        if (sym!='\t' && sym!='\n'){
        text[length] = sym;
        length++;
        text= realloc(text,(length+1)*sizeof(char*));
        }
    }
    text[length] = '\0';
    return text;
}

int check_line(char *text){
	int i=0;
	int flag = 1;
	while (text[i]!=';' && text[i]!='.' && text[i]!='?' && text[i]!='!'){
	int begin=i;
        int first_digit=0;
        int first_alpha=0;
        int last_digit=0;
        int last_alpha=0;
        int alpha_between=0;
        int digit_between=0;
		while(1){
		    if (text[i]==' ' | text[i]==','){
		        break;
		    } 
		    if (text[i]==';' | text[i]=='.' | text[i]=='?'  | text[i]=='!'){
		        break;
		    }
			i++;
		}
		int end=i-1;
		first_digit=isdigit(text[begin]);
		first_alpha=isalpha(text[begin]);
        last_digit=isdigit(text[end]);
		last_alpha=isalpha(text[end]);
		for (int j=begin+1; j<end;j++){
			if (isdigit(text[j])){
				digit_between=1;
			}
			else{
				alpha_between=1;
			}
		}
		if ((first_alpha && last_alpha && alpha_between && !digit_between) || (first_digit && last_digit && digit_between && !alpha_between) || (first_digit && last_alpha && !digit_between && alpha_between) || (last_digit && first_alpha && !digit_between && alpha_between) || (first_digit && last_digit && !digit_between && alpha_between)){
		}
		else{
		    if (end+1-begin>2){
                	flag = 0;
                	break;
            		}
		}
		if (text[i]!=';' && text[i]!='.' && text[i]!='?' && text[i]!='!'){
			i++;
		}
	}
	return flag;
}

int main() {
    int before= 0;
    int after= 0;
    char* text;
    char** new_text = malloc(1*sizeof(char*));
    while (strcmp(text,"Dragon flew away!")){ 
        text = get_text();
        before++;
        if (check_line(text)==1){
            new_text[after] = text;
            after++;
            new_text = realloc(new_text, (after+1)*sizeof(char*));
        }
    }
    for (int i = 0; i <after ; i++){
        puts(new_text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", before-1,after-1);
    return 0;
}
