#include"formattext.h"

wchar_t* slice(wchar_t* str, int start, int end){
	wchar_t *res, *try;
	try = calloc( (end - start + 1), sizeof(wchar_t) );
	if(try != NULL){
		res = try;
	}else{
		wprintf(L"In func slice. Не удалось выделить память.\n");
		return L"";
	}
	for(int i = start; i < end; i++)
		res[i - start] = str[i];
	res[end - start] = L'\0';
	return res;
}


wchar_t* wstr_tolower( wchar_t* first_str){
        wchar_t*res, *try;
	try = (wchar_t*)calloc( wcslen(first_str)+1, sizeof(wchar_t));
        if(try != NULL){
		res = try;
	} else {
		wprintf(L"func wstr_tolower. Не удалось выделить память, возможно некорректное сравнение.\n");
		return first_str;
	}
	for(int i = 0; i < wcslen(first_str) - 1; i++)
                res[i] = towlower(first_str[i]);
	res[wcslen(first_str)-1] = '.';
	res[wcslen(first_str)] = '\0'; 
	return res;
}


wchar_t* get_second_word(struct Text text, int index){
	wchar_t *temp, *pc, *res, *str;
	res = malloc( sizeof(wchar_t)*(wcslen(text.sentences[index].str) + 1));
	if(res != NULL){
		str = res;
	} else {
		wprintf(L"func get_second_word. Не удалось выделить память\n");
		return L"";
	}
	wmemcpy(str, text.sentences[index].str, (wcslen(text.sentences[index].str) + 1));
	if(text.sentences[index].words_number >= 2){
		temp = wcstok(str, L",. ", &pc);
		temp = wcstok(NULL, L",. ", &pc);
		res = slice(temp, 0, wcslen(temp));
		return res;
	} else {
		return L"";
	}
}


int compare(const void* sent1, const void* sent2){
	
	struct Sentence* p1 = (struct Sentence*) sent1;
	struct Sentence* p2 = (struct Sentence*) sent2;

	struct Sentence first = *p1;
	struct Sentence second = *p2;

	int len1, len2;
	wchar_t *word1, *word2, *pc, *str1, *str2, *try;
	
	if(first.words_number < 3){
		len1 = 0;
	} else {
		try = calloc(wcslen(first.str), sizeof(wchar_t));
        	if(try != NULL){
			str1 = try;
		} else {
			wprintf(L"Не удалось выделить память в функции compare\n");
		}
		wmemcpy(str1, first.str, wcslen(first.str));
		word1 = wcstok(str1, L",. ", &pc);
		word1 = wcstok(NULL, L",. ", &pc);
		word1 = wcstok(NULL, L",. ", &pc);
		len1 = wcslen(word1);
		free(str1);
	}

	if(second.words_number < 3){
		len2 = 0;
	} else {
		try = calloc(wcslen(second.str), sizeof(wchar_t));
        	if(try != NULL){
			str2 = try;
		} else {	
			wprintf(L"Не удалось выделить память в функции compare\n");
		}
		wmemcpy(str2, second.str, wcslen(second.str));
		word2 = wcstok(str2, L",. ", &pc);
		word2 = wcstok(NULL, L",. ", &pc);
		word2 = wcstok(NULL, L",. ", &pc);
		len2 = wcslen(word2);
		free(str2);
	}

	if(len1 > len2)
		return 1;
	if(len1 == len2)
		return 0;
	if(len1 < len2)
		return -1;
}


int numbers_inside(wchar_t *str){
	int i = 0, c = 0, start = 0, finish = wcslen(str) - 1;
	wchar_t coma[] = L",", fullstop[] = L".";
	if(isdigit(str[i]))
		while(isdigit(str[i]))
			i ++;
	start = i;
	if(str[finish] == L',' || str[finish] == L'.')
		finish --;
	i = finish;
	if(isdigit(str[i]))
		while((isdigit(str[i])) && (i > 0))
			i --;
	finish = i + 1;

	
	while(start < finish){	
		if(c == 0){
			if (isdigit(str[start]))
				return 1;
		}
		start ++;
	}

	return 0;
}


struct Text command_4(struct Text text){
	
	for(int i = 0; i < text.sents_number; i++){
		int j = 1;
		while(j < wcslen(text.sentences[i].str)){	
			if((text.sentences[i].str[j] != L' ') && (text.sentences[i].str[j] != L',') && (text.sentences[i].str[j] != L'.')){
				if(text.sentences[i].str[j] == text.sentences[i].str[j-1]){
					memmove(text.sentences[i].str + j - 1, text.sentences[i].str + j, (wcslen(text.sentences[i].str) - j + 1) * sizeof(wchar_t));
				} else {
					j++;
				}
			}else{j++;}
		}
	}
	return text;
}


void command_3 (struct Text text){
	wchar_t *str, *try, **tryr, *pc, *temp, **words, coma[] = L",", fullstop[] = L".";
	int c, counter, flag, sum;
	for(int i = 0; i < text.sents_number; i ++){
		c = 0;
		try = calloc(wcslen(text.sentences[i].str) + 1, sizeof(wchar_t));
		if(try != NULL){
			str = try;
		} else {
			wprintf(L"Не удалось выделить память в функции command_3\n");
			continue;
		}
		wmemcpy(str, text.sentences[i].str, wcslen(text.sentences[i].str) + 1);
		temp = str;
		do{
			temp = wcsstr(temp + 1, L",");
			c ++; // количество запятых + 1 точка
		}while(temp != NULL);
		sum = text.sentences[i].words_number + c;
		tryr = calloc(sum, sizeof(wchar_t*));
		if(tryr != NULL){
			words = tryr;
		} else {
			free(str);
			continue;
		}
		
		c = 0;
		flag = 0;
		temp = wcstok(str, L" ", &pc);
		do{
			
			words[c] = temp;
			if(wcsstr(temp, L",") != NULL){
				words[c] = slice(temp, 0, wcslen(temp) - 1);
				c ++;
				words[c] = coma;
			}
			if(wcsstr(temp, L".") != NULL){
				words[c] = slice(temp, 0, wcslen(temp) - 1);
				c ++;
				words[c] = fullstop;
			}
			c ++;

                        if(numbers_inside(temp))
				flag = 1;

			temp = wcstok(NULL, L" ", &pc);
		}while(temp != NULL);

		counter = 1;
		if(flag){
			if(wcslen(words[0]) > 2){
				if(numbers_inside(words[0])){
					wprintf(L"\033[32m%ls\033[0m", words[0]);//green
				}else{
					wprintf(L"%ls", words[0]);
				}
			}else{
				wprintf(L"%ls", words[0]);
			}
			while(counter < c){
				if(wcsstr(words[counter], L",") != NULL){
					wprintf(L",");
				}else if(wcsstr(words[counter], L".") != NULL){
					wprintf(L".");
				}else{
					if(numbers_inside(words[counter])){
						wprintf(L"\033[32m %ls\033[0m", words[counter]);//green
					}else{
						wprintf(L" %ls", words[counter]);								}
				}		
				counter ++;
			}
			wprintf(L"\n");
			free(str);
			free(words);
		}
	}
}


struct Text command_2 (struct Text text){
	qsort(text.sentences, text.sents_number, sizeof(struct Sentence), compare);
	return text;
}


struct Text command_1 (struct Text text){
	wchar_t *str, *second_word, *try, fullstop[] = L".\0";
	int start, last = text.sents_number - 1, end, m, ch, size;
	struct Text result;
	struct Sentence *tryr;
	result.sents_number = text.sents_number;
	tryr = calloc(text.sents_number, sizeof(struct Sentence));
	if(tryr != NULL)
		result.sentences = tryr;

	for(int i = 0; i < text.sents_number; i++){
		if(i == 0){
			second_word = get_second_word(text, last);
                        if(text.sentences[i].words_number != 1){
                                start = (int)(wcsstr(text.sentences[i].str,L" ")-text.sentences[i].str);
                                if(second_word != L""){
                                str = slice(text.sentences[i].str,start, wcslen(text.sentences[i].str));
                                }else{
                                str =slice(text.sentences[i].str,start+1,wcslen(text.sentences[i].str));
                                }

			}else{
				str = L"";
			}
			m = wcslen(second_word) + wcslen(str);
			try = (wchar_t *)calloc(m + 1,sizeof(wchar_t));	
			if(try != NULL)
				result.sentences[i].str = try;
			wcscat( result.sentences[i].str, second_word); //second_word
			wcscat( result.sentences[i].str, str);// + str
			result.sentences[i].words_number = text.sentences[i].words_number;
			if(wcslen(second_word) == 0)
                                result.sentences[i].words_number --;
		}else{
                       	second_word = get_second_word(text, i-1);
			free(result.sentences[i].str );
			result.sentences[i].str = malloc( 1*sizeof(wchar_t));
			if(text.sentences[i].words_number != 1){
				start = (int)(wcsstr(text.sentences[i].str,L" ")-text.sentences[i].str);
				if(second_word != L""){
				str = slice(text.sentences[i].str,start, wcslen(text.sentences[i].str));
				}else{
				str =slice(text.sentences[i].str,start+1,wcslen(text.sentences[i].str));
				}
			}else{
				str = L"";
			}
			m = wcslen(second_word) + wcslen(str) + 1;
			try = realloc(result.sentences[i].str, (m)*sizeof(wchar_t));
			if(try != NULL)
				result.sentences[i].str = try;	
			wmemcpy(result.sentences[i].str, second_word, wcslen(second_word));
			wcscat( result.sentences[i].str, str);
			result.sentences[i].words_number = text.sentences[i].words_number;
			if(wcslen(second_word) == 0)
				result.sentences[i].words_number --;
		}
	
		if(result.sentences[i].str[wcslen(result.sentences[i].str) - 1] != L'.')
			wcscat(result.sentences[i].str, fullstop);
	}
	for(int i = 0; i < text.sents_number; i ++)
		free(text.sentences[i].str);
	free(text.sentences);

	return result;
}


struct Sentence *delete_repeated_sentences(struct Sentence *sentences, int *p){
	int i = 1, c = 0, j = 0, res_counter = 1, sents_num = *p;
	struct Sentence* result, *reserv_result;
	wchar_t* first, *second, *wstr;
	reserv_result = calloc( 1, sizeof(struct Sentence));
	if(reserv_result != NULL)
		result = reserv_result;
	result[0].str = sentences[0].str;
	result[0].words_number = sentences[0].words_number;

	while( i < sents_num){ /* 1 --> sents_num - 1 */
		first = wstr_tolower(sentences[i].str);
		j = 0;
		c = 0;
		while( j < i){
			second = wstr_tolower(sentences[j].str);
			if(wcscmp(first, second) == 0)
				c = 1;
			j++;
		}
		if(c == 0){
			res_counter ++;
			reserv_result = realloc( result, res_counter*sizeof(struct Sentence));
			if(reserv_result != NULL)
				result = reserv_result;
			result[res_counter-1].str = sentences[i].str;
			result[res_counter-1].words_number = sentences[i].words_number;
		}else{
			free(sentences[i].str);
		}
		i ++;
	}

	free(sentences);
	*p = res_counter;

	return result;
}



void input_text_free(int n, wchar_t** text_string){
	for(int i = 0; i < n; i++){
                free(text_string[i]);
        }
        free(text_string);
}
