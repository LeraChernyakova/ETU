#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "struct.h"

wchar_t* first_word(struct Sentence *line){
  int size = 25;
  wchar_t* word = malloc(size*sizeof(wchar_t*));
  int sym, i = 0;
  while(1){
    sym = line->sent[i];
    if (sym == ' ' || sym == '.' || sym == ','){ 
      word[i] = '\0';
      break;
    }
    else word[i++] = sym;
    if(i == size) { 
      size *= 2; 
      word = realloc(word, size); 
    } 
  }
  return word;
}

wchar_t* last_word(struct Sentence *line){
  short size = 25;
  wchar_t* word = malloc(size*sizeof(wchar_t*));
  int sym, j, k = 0, i = 2;
  while(1){
    sym = line->sent[line->size-1-i];
    if (sym == ' ' || sym == ','){ 
      word[i] = '\0';
      break;
    }
    else word[k++] = sym;
    if(line->size - i == -1){
      word[k] = '\0';
      break;
    }
    if(i == size){
      size *= 2;
      word = realloc(word, size);
    } 
    i++;
  }
  for (i = 0; i < wcslen(word)/2; i++){
    j = word[i];
    word[i] = word[wcslen(word)-1-i];
    word[wcslen(word)-1-i] = j;
  }
  return word;
}

int is_alright(struct Sentence* line){
  wchar_t *f_word, *l_word;
  f_word = first_word(line);
  l_word = last_word(line);
  if(wcscasecmp(f_word, l_word) == 0) 
    return 1;
  else
    return 0;
}

struct Text* delete_lines(struct Text* text){
  int i, k;
  for (i = 0; i < text->real_amount; i++){
    if (is_alright(text->lines[i]) != 0){
      for (k = i; k < text->real_amount-1; k++)
        text->lines[k] = text->lines[k+1];
        text->real_amount--;
        i--;
    }
  }
  return text;
}

struct Sentence* find_and_change(struct Sentence* line){
  wchar_t* ptr = wcsstr(line->sent, L"полночь");
  if (ptr)
    wmemcpy(ptr, L"midnight", wcslen(L"midnight")-1);

  int fl = 0;
  wchar_t* res = malloc(256*sizeof(wchar_t));
  wchar_t* ptr2, *ptr_res = res, *ptr_line = line->sent;
  wchar_t* repl = L"полдень";
  wchar_t* subs = L"high noon";
  for (; (*ptr_res = *ptr_line); ++ptr_line, ++ptr_res){
    if (!wcsncmp(ptr_line, subs, wcslen(subs))){
      fl = 1;
      wcscpy(ptr_res, repl);
      ptr_line += wcslen(subs)-1;
      ptr_res += wcslen(repl)-1;
    }
  }
  if (fl == 1){
    wcscpy(line->sent, L"");
    line->size = wcslen(res);
    wcscpy(line->sent, res);
  }

  free(res);
  return line;
  
}


struct Text* change_substrings(struct Text* text){
  int i, k;
  for (i = 0; i < text->real_amount; i++)
    find_and_change(text->lines[i]);
  return text;
}
