#include"inputtext.h"

wchar_t** input_text(int* c){
	int n = 0;
	wchar_t **text_string, **reserv_text_string, *reserv, ch = ' ';
	reserv_text_string = malloc( sizeof(wchar_t*)*1 );
	if(reserv_text_string != NULL)
		text_string = reserv_text_string;
	while(ch != '\0'){
		n ++;
		reserv_text_string = (wchar_t **)realloc( text_string, n*sizeof(wchar_t*) );
		if(reserv_text_string != NULL){
			text_string = reserv_text_string;
			reserv = malloc( 100*sizeof(wchar_t) );
			if(reserv != NULL)
				text_string[n - 1] = reserv;
			text_string[n - 1][98] = '\0';
			fgetws(text_string[n - 1], 100, stdin);
			ch = text_string[n - 1][98];

			if(wcslen(text_string[n-1]) == 1){
				free(text_string[n - 1]);
				n --;
				}
		}
	}
	*c = n;

	return text_string;
}


struct Sentence *make_sentences(int n, wchar_t **text_string, int* p){
	struct Sentence *sentences = malloc(sizeof(struct Sentence)), *try;
	int i = 0, start = 0, sentence_counter = 1, hun = 1, r = 0, numb;
	wchar_t *end, *sentence, *try_to_realloc, fullstop[] = L".\0";

	try_to_realloc = calloc( 100, sizeof(wchar_t) );//сборка предложения, будет записано в структуру
	if(try_to_realloc != NULL){
		sentence = try_to_realloc;
	}else{
		wprintf(L"Не удалось выделить память для сборки предложений.\n");
		return sentences;
	}
	while( i < n ){
		end = wcsstr( text_string[i] + r + 1, L"." );
		if(end == NULL){
			wcscat(sentence, slice(text_string[i], start, wcslen(text_string[i])));
			hun ++;
			i ++;
			r = 0;
			start = 0;
			try_to_realloc = realloc( sentence, hun * 100 * sizeof(wchar_t) );
			if(try_to_realloc != NULL){
				sentence = try_to_realloc;
			} else {
				wprintf(L"Не удалось выделить память для текущего редложения.\n");
				free(sentence);
				try_to_realloc = calloc(100, sizeof(wchar_t));
				if(try_to_realloc != NULL){
					sentence = try_to_realloc;
				} else {
					return sentences;
				}
			}
		} else {
			wcscat(sentence, slice(text_string[i],start, (int)(end - text_string[i])));
			wcscat(sentence, fullstop);
			r = (int)(end - text_string[i]);

			try = realloc( sentences, sentence_counter*sizeof(struct Sentence));
			if(try != NULL){
				sentences = try;
			}else{
				return sentences;
			}
			sentences[sentence_counter-1].str = (wchar_t*)malloc((wcslen(sentence) + 1)*sizeof(wchar_t));
			wmemcpy(sentences[sentence_counter-1].str, sentence, wcslen(sentence) + 1);

			numb = 0;
                        for(int j = 0; j < wcslen(sentence); j++)
                                if(iswspace(sentence[j]))
                                        numb ++;
			sentences[sentence_counter-1].words_number = numb + 1;
			sentence_counter ++;

			if(i != n)
				start = ((int)(end - text_string[i]) + 2) % 99;
			free(sentence);
			sentence = calloc( 100, sizeof(wchar_t) );
			hun = 1;
			if((int)(end - text_string[i]) == 98 || (int)(end - text_string[i]) == 99){					r = 0;
				i ++;
			}
		}
	}
	*p = sentence_counter;

	return sentences;
}
