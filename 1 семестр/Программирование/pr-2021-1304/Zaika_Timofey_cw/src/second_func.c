#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_STEP 100
#define CRASH_MEMORY_MSG L"Ошибка выделения памяти"

#include <wchar.h>
#include <locale.h>

#include "textio.h"

wchar_t* check_month(wchar_t *inp_str){
	wchar_t *rus_months[] = {L"января", L"февраля", L"марта", L"апреля", L"мая", L"июня", L"июля", L"августа", L"сентября", L"октября", L"ноября", L"декабря"};
	wchar_t *eng_months[] = {L"january", L"february", L"march", L"april", L"may", L"june", L"july", L"august", L"september", L"october", L"november", L"december"};

	for(int i=0; i<12; i++){
		if(wcscasecmp(inp_str, rus_months[i]) == 0 || wcscasecmp(inp_str, eng_months[i]) == 0){
			wchar_t *buf = malloc(3*sizeof(wchar_t*));
			if(!buf){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
			if(i<10){
				swprintf(buf, 3, L"0%d", i+1);
			} else {
				swprintf(buf, 3, L"%d", i+1);
			}
			return buf;
		}
	}
}

wchar_t* check_date(wchar_t *inp_str){
	wchar_t *dates[] = {L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10",
						L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", 
						L"21", L"22", L"23", L"24", L"25", L"26", L"27", L"28", L"29", L"30", L"31"};

	for(int i=0; i<31; i++){
		if(wcscmp(inp_str, dates[i]) == 0){
		wchar_t *buf = malloc(3*sizeof(wchar_t*));
		if(!buf){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
			if(i<10){
				swprintf(buf, 3, L"0%d", i+1);
			} else {
				swprintf(buf, 3, L"%d", i+1);
			}
			return buf;
		}
	}
}

void change_date(struct Text *text){
	wchar_t sep[10] = L" ,!?;\n";

	for(int i=0; i<text->n; i++){
		int cur_elem = 0;
		wchar_t **work_sent = malloc(MEM_STEP*sizeof(wchar_t*));
		if(!work_sent){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}

		wchar_t *cur_sent = text->sents[i]->str;
		wchar_t temp_sent[wcslen(cur_sent)];
		wcscpy(temp_sent, cur_sent);

		wchar_t *istr;
		wchar_t *pwc;
		istr = wcstok(temp_sent, sep, &pwc);
		while(istr != NULL){
			wchar_t *temp = calloc(*istr, sizeof(wchar_t*));
			if(!temp){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
			wcscpy(temp, istr);
			work_sent[cur_elem] = temp;
			cur_elem++;
			istr = wcstok(NULL, sep, &pwc);
		}

		wchar_t **temp_date = malloc(3*sizeof(wchar_t*));
		if(!temp_date){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}

		for(int j=0; j<cur_elem-3; j++){
			if(wcscmp(work_sent[j+3], L"y.") == 0 || wcscmp(work_sent[j+3], L"г.") == 0){
				wchar_t* date = check_date(work_sent[j]);
				if(date != NULL){
					temp_date[0] = date;
					wchar_t* num_mounts = check_month(work_sent[j+1]);
					if(num_mounts != NULL){
						temp_date[1] = num_mounts;
						if(work_sent[j+2][0] > L'0' && work_sent[j+2][0] <= L'9'){
							temp_date[2] = work_sent[j+2];
						} else {
							break;
						}
					} else {
						break;
					}
				} else {
					break;
				}
			}		
		}


		wchar_t *replace = malloc(30*sizeof(wchar_t*));
		if(!replace){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
		swprintf(replace, 30, L"%ls/%ls/%ls", temp_date[0], temp_date[1], temp_date[2]);

		int wchar_start = 0;
		int wchar_end = 0;

		if(temp_date[0] != NULL && temp_date[1] != NULL && temp_date[2] != NULL){
			for(int i=0; i<wcslen(cur_sent); i++){
				if(cur_sent[i] == temp_date[0][1] || cur_sent[i] == temp_date[0][0]){
					wchar_start = i;
					int cur_num_year = 0;
					for(int j=i+1; j<wcslen(cur_sent); j++){
						if(cur_sent[j] == temp_date[2][cur_num_year]){
							wchar_end = j;
							cur_num_year++;
						}
					}
					if(wchar_end == 0){
						wchar_start = 0;
					} else {
						break;
					}
				}
			}
		}

		memmove(cur_sent+wchar_start, replace, ((wchar_end-wchar_start) * sizeof(wchar_t)));

		free(temp_date);
		free(replace);
		for(int i=0; i<cur_elem; i++){
			free(work_sent[i]);
		}
		free(work_sent);
	}
}