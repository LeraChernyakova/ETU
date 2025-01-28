#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include "struct.h"
#define MAX_SENT 20
#define MAX_SYM 100


struct Sentence* read_line(void){
  wchar_t buf[MAX_SYM];
  int sym, k=0, fl = 1, flag = 0;
  while ((sym = getwchar()) != EOF){
    if (sym == '\n')
      if (flag)
        return NULL; 
      else 
        flag = 1;
    else 
      flag = 0;
    if (isspace(sym) && fl)
      continue;
    fl = 0;
    buf[k++] = sym;
    if (sym == '.'){
      struct Sentence* res = malloc(sizeof(struct Sentence*));
      buf[k] = '\0';
      res->size = k+1;
      res->sent = malloc(res->size*sizeof(wchar_t)); 
      wcsncpy(res->sent, buf, res->size);
      return res;
    }
    if (k == MAX_SYM) 
      return NULL;
  }
  return NULL;
}

struct Text* read_text(void){
  struct Text* txt;
  struct Sentence* line;
  int i = 0, j = 0, k;
  txt = malloc(sizeof(struct Text));
  txt->max_amount = MAX_SENT;
  txt->real_amount = 0;
  txt->lines = malloc(MAX_SENT*sizeof(struct Sentence*)); 
  while ((line = read_line()) != NULL) {
    txt->lines[txt->real_amount++] = line;
    if (txt->real_amount == txt->max_amount){
      txt->max_amount *= 2;
      txt->lines = realloc(txt->lines, txt->max_amount);
    }
  }
  int fl = 0;
  for (i = 0; i < txt->real_amount; i++){
    for (j = i + 1; j < txt->real_amount; j++){
      if ((wcscasecmp(txt->lines[i]->sent, txt->lines[j]->sent)) == 0) {
        for (k = j; k < txt->real_amount-1; k++)
          txt->lines[k] = txt->lines[k+1];
        txt->real_amount--;
        j--;
        fl = 1;
      }
    }
  }
  return txt;
}

void show_text(struct Text* txt){
  for (int i = 0; i < txt->real_amount; i++){
    printf("%ls ",txt->lines[i]->sent);
  }
  printf("\n");
}
