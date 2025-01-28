#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "task_1.h"

int count(const wchar_t* tmp,int N){
    int count_al = 0;
    for (int k = 0; k < N; k++) {
        if (tmp[k] != '?' && tmp[k] != '*') {
            count_al++;
        }
    }
    return count_al;
}

int repeate_mask(wchar_t** masks, wchar_t* mask,int N){
    for (int i = 0; i < N;i++){
        if (!wcscmp(masks[i],mask)){
            return 0;
        }
    }
    return 1;
}

void task_1(Sentence * sent){
    int size_mask = 30;
    int size_mask2 = 100;
    int size_mask_word = 20;
    wchar_t** tmp2;
    wchar_t** tmp4;
    wchar_t* tmp3;
    wchar_t** mask_1 = (wchar_t**) malloc(size_mask*sizeof(wchar_t*));//Первичные маски
    wchar_t** mask_2 = (wchar_t**) malloc(size_mask2*sizeof(wchar_t*));//Готовые маски
    int count_al;
    int m;
    int mv1;
    int zi1;//Смещение 1 слова (от i)
    int zi2;//Смещение 2 слова (от j)
    int count_mask = 1;
    mask_1[0] = sent->words[0].word;

    int max_count_al = 0;
    int count_mask_2 = 0;
    for (int i = 1; i < sent->count_words;i++){
        for (int j = 0;j<count_mask;j++){
            zi1 = 0;
            zi2 = 0;
            if (mask_1[j][wcslen(mask_1[j])-1] == '*'){
                mask_1[j][wcslen(mask_1[j])-1] = '\0';
            }
            if (mask_1[j][0] == '*'){
                for (int k = 0; k<wcslen(mask_1[j]);k++){
                    mask_1[j][k] = mask_1[j][k+1];
                }
            }
            if(sent->words[i].size_word >= wcslen(mask_1[j])){ 
                while (zi2 < wcslen(mask_1[j])) {
                    if (count_mask_2 >= size_mask2 -1){
                        size_mask2+=500;
                        tmp4 = (wchar_t**)realloc(mask_2,size_mask2*sizeof(wchar_t*));
                        mask_2 = tmp4;
                    }
                    wchar_t *tmp = (wchar_t *) malloc(size_mask_word * sizeof(wchar_t));
                    if (zi1 < sent->words[i].size_word-1) { //Эта строка гарантирует, что нулевые элементы сравниваются в другом условии
                        m = 1;
                        mv1 = 0;
                        tmp[0] = '*';
                        while (m <= zi1+1 && m < wcslen(mask_1[j])+1) {
                        	if(m == size_mask_word-2){
                                size_mask_word+=15;
                                tmp3 = (wchar_t*)realloc(tmp,size_mask_word*sizeof(wchar_t));
                                tmp = tmp3;
                            }
                            if (mask_1[j][m-1] ==
                                sent->words[i].word[sent->words[i].size_word - 1 - zi1 + mv1]) {
                                tmp[m] = mask_1[j][m-1];
                            } else { tmp[m] = '?'; }
                            m++;
                            mv1++;
                        }
                        tmp[m] = '*';
                        tmp[m+1] = '\0';
                        count_al = count(tmp,m);
                        //wprintf(L"%ls  ", tmp);
                        if (count_al != 0 && repeate_mask(mask_2,tmp, count_mask_2)) {
                            mask_2[count_mask_2] = tmp;
                            count_mask_2++;
                        }
                        
                        zi1++;
                    } else {
                        m = 0;
                        mv1 = 0;
                        tmp[0] = '*';
                        m++;
                        while (zi2 + m-1 < wcslen(mask_1[j]) && zi2 + m-1 < sent->words[i].size_word) {
                        	if(m == size_mask_word-2){
                                size_mask_word+=15;
                                tmp3 = (wchar_t*)realloc(tmp,size_mask_word*sizeof(wchar_t));
                                tmp = tmp3;
                            }
                            if (mask_1[j][zi2 + m-1] == sent->words[i].word[m-1]) {
                                tmp[m] = sent->words[i].word[m-1];
                            } else { tmp[m] = '?'; }
                            m++;
                            mv1++;
                        }

                        tmp[m] = '*';
                        tmp[m+1] = '\0';
                        count_al = count(tmp,m);
                        //wprintf(L"%ls  ", tmp);
                        if (count_al != 0 && repeate_mask(mask_2,tmp, count_mask_2)) {
                            mask_2[count_mask_2] = tmp;
                            count_mask_2++;
                        }
                        
                        zi2++;
                    }
                }
            }else{
                while (zi2 < sent->words[i].size_word) {
                    if (count_mask_2 >= size_mask2 -1){
                        size_mask2+=50;
                        tmp4 = (wchar_t**)realloc(mask_2,size_mask2*sizeof(wchar_t*));
                        mask_2 = tmp4;
                    }
                    wchar_t *tmp = (wchar_t *) malloc(size_mask_word * sizeof(wchar_t));
                    if (zi1 < wcslen(mask_1[j])-1){
                        m = 1;
                        mv1 = 0;
                        tmp[0] = '*';
                        while (m-1 <= zi1 && m-1 < sent->words[i].size_word){
                        	if(m == size_mask_word-2){
                                size_mask_word+=15;
                                tmp3 = (wchar_t*)realloc(tmp,size_mask_word*sizeof(wchar_t));
                                tmp = tmp3;
                            }
                            if (sent->words[i].word[m-1] == mask_1[j][wcslen(mask_1[j])-1-zi1+mv1]) {
                                tmp[m] = mask_1[j][wcslen(mask_1[j])-1-zi1+mv1];
                            } else { tmp[m] = '?'; }
                            m++;
                            mv1++;
                        }
                        tmp[m] = '*';
                        tmp[m+1] = '\0';
                        count_al = count(tmp,m);
                        //wprintf(L"%ls  ", tmp);
                        if (count_al != 0 && repeate_mask(mask_2,tmp, count_mask_2)) {
                            mask_2[count_mask_2] = tmp;
                            count_mask_2++;
                        }
               
                        zi1++;
                    } else {
                        m = 1;
                        mv1 = 0;
                        tmp[0] = '*';
                        while (zi2 + m-1 < sent->words[i].size_word && zi2 + m-1 < wcslen(mask_1[j])) {
                        	if(m == size_mask_word-2){
                                size_mask_word+=15;
                                tmp3 = (wchar_t*)realloc(tmp,size_mask_word*sizeof(wchar_t));
                                tmp = tmp3;
                            }
                            if (sent->words[i].word[zi2 + m-1] == mask_1[j][m-1]) {
                                tmp[m] = sent->words[i].word[zi2+m-1];
                            } else { tmp[m] = '?'; }
                            m++;
                        
                        }
                        tmp[m]='*';
                        tmp[m+1] = '\0';

                        count_al = count(tmp,m);
                        //wprintf(L"%ls %d,", tmp,count_al);
                        if (count_al != 0 && repeate_mask(mask_2,tmp, count_mask_2)) {
                            mask_2[count_mask_2] = tmp;
                            count_mask_2++;
                        }
                        
                        zi2++;
                    }
                }
            }
        }
        for(int p = 0;p < count_mask_2;p++){
            if(p >= size_mask-2){
                size_mask+=20;
                tmp2 = (wchar_t**)realloc(mask_1,size_mask*sizeof(wchar_t*));
                mask_1 = tmp2;
            }
            mask_1[p] = mask_2[p];
        }
        count_mask = count_mask_2;
        count_mask_2 = 0;
    }
	
    int max_size_mask = 0;
    int rec = 0;
    int count_ready_mask = 0;
    wchar_t** rec_masks = (wchar_t**)malloc(count_mask*sizeof(wchar_t*));
    for(int q = 0 ;q < count_mask;q++){
        if(count(mask_1[q],(int)wcslen(mask_1[q])) >= max_count_al){
            max_count_al = count(mask_1[q],(int)wcslen(mask_1[q]));
            max_size_mask = (int)wcslen(mask_1[q]);
        }
    }

    for (int q = 0; q < count_mask;q++){
        if (count(mask_1[q],(int)wcslen(mask_1[q])) == max_count_al){
            rec_masks[rec] = mask_1[q];
            if (max_size_mask < wcslen(rec_masks[rec])){
                max_size_mask = (int)wcslen(rec_masks[rec]);
            }
            rec++;
        }else{
            free(mask_1[q]);
        }
    }

    wchar_t** ready_masks = (wchar_t**)malloc(rec*sizeof(wchar_t*));
    for (int q = 0; q < rec;q++){
        if(wcslen(rec_masks[q]) == max_size_mask){
            ready_masks[count_ready_mask] = rec_masks[q];
            count_ready_mask++;
        }
    }
    sent->masks = ready_masks;
    sent->count_mask = count_ready_mask;
}

