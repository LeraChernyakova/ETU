#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <time.h>
#define MEM_STEP 5


struct Word{
	char * begin;
	int size;
	int alph;
	char end;
};

struct Sentence{
	char *str;
	int size;
	struct Word* words;
	int wordsCount;
};

struct Text{
	struct Sentence** sents;
	int size;
	int n;
};
//*****************************************************************************
int splitWords(struct Sentence* sent){

	int size = MEM_STEP;
	struct Word* buf = malloc(size*sizeof(struct Word));

	int j = 0;
	int lenCount = 0;
	int inWord = 0;
	char *temp_buf;
	int alphaCount;

	for (int i = 0; i < sent->size; i++){

		if (inWord == 0 && (isspace(sent->str[i]) || sent->str[i] == ',') == 0){

			buf[j].begin = &sent->str[i];
			inWord = 1;
			lenCount = 1;
			alphaCount = 0;
			if (isalpha(sent->str[i])){
				alphaCount++;
			}

		} else if (inWord == 1 && (isspace(sent->str[i]) || sent->str[i] == ',' || sent->str[i] == '.')){
			buf[j].end = sent->str[i];
			buf[j].alph = alphaCount;
			buf[j++].size = lenCount;

			inWord = 0;
			temp_buf = malloc((lenCount+1)*sizeof(char));
			temp_buf = memcpy(temp_buf, buf[j-1].begin, lenCount*sizeof(char));
			temp_buf[lenCount] = '\0';
			buf[j-1].begin = temp_buf;



			if (j == size) {
				size += MEM_STEP;
				buf = realloc(buf, size*sizeof(struct Word));
			}

		} else {
			lenCount++;
			if (isalpha(sent->str[i])){
				alphaCount++;
			}
		}

	}
	sent->words = buf;
	return j;

}


void delete_sents(struct Sentence **sents, int *n){

	struct Sentence *sent_1, *sent_2;

	int i = 0;
	int j;

	while (i < *n-1){

		sent_1 = sents[i];
		j = i+1;
		while (j < *n){
			
			sent_2 = sents[j];

			if (strcasecmp(sent_1->str, sent_2->str) == 0){
				free(sent_2->str);
				free(sent_2);
				memmove(&sents[j], &sents[j+1], (*n-j-1)*sizeof(struct Sentence*));
				*n -= 1;
			} else {
				j++;
			}
		}
		i++;
		j = i + 1;
	}
}





struct Sentence* readSentence();

struct Text readText(){
	printf("Введите текст\n");
	int size=MEM_STEP;
	struct Sentence** text = malloc(size*sizeof(struct Sentence*));
	int n=0;
	struct Sentence* temp;
	int nlcount=0;
	do{
		temp = readSentence();
		
		
		if(temp->str[0]=='\n'){
			nlcount++;
			free(temp->str);
			free(temp);
		}else{
			nlcount=0;
 			text[n]=temp;
       		n++;

       		if (n == size){
       			size += MEM_STEP;
       			text = realloc(text, size*sizeof(struct Sentence*));
       		}
		}		
	}while(nlcount<2);
	
	delete_sents(text, &n);

	struct Text txt;
	txt.size = size;
	txt.sents = text;
	txt.n = n;

 
	return txt;
}


struct Sentence* readSentence(){
 	int size = 5;
	char *buf = malloc(size*sizeof(char));
	char temp;
	int n = 0;
	do{  	
		if(n>=size-2){
			char *t = realloc(buf,size+MEM_STEP);
			if (!t){
				printf("Error:");
				return NULL;
			}
			size += MEM_STEP;
			buf = t;
		}
		  
	   	temp=getchar();
		buf[n]=temp;
		n++;

	}while(temp!='\n' && temp!='.' && temp!='!');
	buf[n]='\0';
	struct Sentence *sentence = malloc(sizeof(struct Sentence));
	
	int count = 0;
	for (int i = 0; buf[i] == ' '; i++){
		count++;
	}
	memmove(buf, buf+count, strlen(buf)-count+1);


	sentence->str = buf;
	sentence->size = size;	


	sentence->wordsCount = splitWords(sentence);


	return sentence;
}

void free_text(struct Text* text){
	for(int i =0; i < text->n; i++){
		for(int j = 0 ;j < text->sents[i]->wordsCount;j++){
			free(text->sents[i]->words[j].begin);
		}
		free(text->sents[i]->words);
		free(text->sents[i]);
	}
	free(text->sents);
}
//*****************************************************************************
void sentProc(struct Sentence* sent, int k, int m){
	int len = strlen(sent->str);
	char *cur_str = sent->str;
	memmove(cur_str+k, cur_str+k+m, len-m-k+1);
}

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4

int cmp(const void* a, const void* b){
	struct Sentence **first_sent = (struct Sentence **) a;
	struct Sentence **second_sent = (struct Sentence **) b;

	if ((*first_sent)->words[(*first_sent)->wordsCount-1].size > (*second_sent)->words[(*second_sent)->wordsCount-1].size){
		return 1;
	} else if ((*first_sent)->words[(*first_sent)->wordsCount-1].size < (*second_sent)->words[(*second_sent)->wordsCount-1].size){
		return -1;
	}
	return 0;

}

void sortLast(struct Text* txt){

	qsort(txt->sents, txt->n, sizeof(struct Sentence*), cmp);

}

//4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
// 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
void num_word(struct Text* text){
	for (int i=0; i<text->n; i++){
		for (int j = 0; j < text->sents[i]->wordsCount; j++){
			if (text->sents[i]->words[j].alph != 0){
				printf("%d%s%c", text->sents[i]->words[j].alph, text->sents[i]->words[j].begin, text->sents[i]->words[j].end);
			} else{
				printf("%s%c", text->sents[i]->words[j].begin, text->sents[i]->words[j].end);
			}
		}
	}
	printf("\n");
}
// 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 

// 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 
void odd_sents(struct Text* text){
	struct Sentence** sp;
	struct Word* wp;
	
	for (sp = text->sents+text->n-1; sp >= text->sents; sp--){
		for (wp = (*sp)->words; wp < (*sp)->words+(*sp)->wordsCount; wp++)
			if (wp->alph % 2 == 0) break;
		if (wp < (*sp)->words+(*sp)->wordsCount) continue;
		for (wp = (*sp)->words; wp < (*sp)->words+(*sp)->wordsCount; wp++)
			free(wp->begin);
		free((*sp)->words);
		free((*sp)->str);
		free((*sp));
		text->n--;
		memmove(sp, sp+1, (text->n+text->sents-sp)*sizeof(struct Sentence*));
	}
}
// 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 
// 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
int date_check(struct Word* word_p){
	if (word_p->size != 10) return 0;

	char* ch= word_p->begin;
	if ( ! (isdigit(ch[0]) && isdigit(ch[1])&&(ch[2]=='/') &&
	 		isdigit(ch[3]) && isdigit(ch[4])&&(ch[5]=='/') &&
	 		isdigit(ch[6]) && isdigit(ch[7])&&isdigit(ch[8]) &&
	 		isdigit(ch[9]) && (ch[10]=='\0')))
	{		
		return 0;	
	}
	struct tm* datetime = malloc(sizeof(struct tm)); 
	long int status= strptime(ch, "%d/%m/%Y", datetime);
	free(datetime);

	if ((char*)status == NULL) {
		return 0;
	}
	
	return 1;
}



void print_date(struct Text* text){
	char* ch;
	int flag;

	struct tm tm = *localtime(&(time_t){time(NULL)});
    time_t current_time_in_second= mktime(&tm);
	for (struct Sentence** sent_p = text->sents;
		sent_p < text->sents+text->n;           
		sent_p++){                              
		int is_sent_have_date = 0;
		for (struct Word* word_p = (*sent_p)->words;
		 	word_p < (*sent_p)->words+(*sent_p)->wordsCount; 
		 	word_p++)
		{
			is_sent_have_date = date_check(word_p);
			if(is_sent_have_date != 0) break;
		}		
		if(is_sent_have_date == 0) continue;
		for(struct Word* word_p = (*sent_p)->words;
		 	word_p < (*sent_p)->words+(*sent_p)->wordsCount; 
		 	word_p++)
		 	{	int is_date = date_check(word_p);
		 		if(is_date == 0){
		 			 printf("%s%c", word_p->begin,word_p->end);
				}else{
					struct tm* datetime = malloc(sizeof(struct tm)); 
					strptime(ch, "%d/%m/%Y", datetime);
					time_t date_in_seconds= mktime(datetime);
					free(datetime);
					if (date_in_seconds > current_time_in_second) {
					 	printf("\033[0;31m");
					 	printf("%s", word_p->begin);
						printf("\033[0m");
					} else {
						printf("%s", word_p->begin);
					}
					printf("%c ",word_p->end);
				}
			}
			//printf("\n");
	}
	printf("\n");
} 
// 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
int main(){
	
	struct Text text = readText();


	char mode = -1;
	printf("\033[0;32m");
	printf(">> Функции:\n");
	printf(">> 1. Вывод предложений с датами\n");
	printf(">> 2. Удалить предложения в которых каждое слово содержит нечетное количество букв. \n");
	printf(">> 3. Вывод количество букв перез каждым словом\n");
	printf(">> 4. Отсортировать предложения по возрастанию длины последнего слова\n");
	printf(">> Для выхода из программы ввести (q)\n");
	printf("\033[0m");
	char trash;

	while(mode != 0) {
		printf("Выбор функции:");
		scanf("%c", &mode);
		scanf("%c", &trash);
		switch(mode){
			case '1':
				print_date(&text);
				break;
			case '2':
				odd_sents(&text);
				for (int i = 0; i < text.n; i++){
					printf("%s", text.sents[i]->str);
				}
				printf("\n");
				break;
			case '3':
				num_word(&text);
				break;
			case '4':
				sortLast(&text);
				for (int i = 0; i < text.n; i++){
					printf("%s", text.sents[i]->str);
				}
				printf("\n");
				break;
			case 'q':
				free_text(&text);
				return 0;
			default:
				printf("Повторите попытку :)\n");
				
		}
	}
}
