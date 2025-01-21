#pragma once
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#define Size 50
#ifndef __Structs__
        #define __Structs__
        struct sentense{
                wchar_t *str;
                int kol;
                int *word;
                int kol_word;};

        struct text{
                struct sentense **sen;
                int kol_sen;
                int kol_sym;};
#endif
void free_for_two(wchar_t **s,int size);
int mask_fun(wchar_t *str,int kol,wchar_t *mask,int size);
int strtok_for_mask(struct text Text,wchar_t *mask,int size);
int cmp(const void *a,const void *b);
int cmp_1(const void *a,const void *b);
int cmp_2(const void *a,const void *b);
wchar_t * qsort_for_3(struct sentense sen);
struct text del_sentense(struct text t);
void free_for_text(struct text t);
struct text removeSentense(struct text t);
