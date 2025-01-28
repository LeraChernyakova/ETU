#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cmp(const void* a,const void* b) {
  return strcmp(*(char**)a,*(char**)b);
}

int main(){
  char* text = malloc(1001*sizeof(char));
  fgets(text, 1001, stdin);
  text[strlen(text)] = '\0';
  char* str = malloc(31*sizeof(char));
  fgets(str, 31, stdin);
  str[strlen(str)] = '\0';

  int words_num = 20;
  char** words = calloc(words_num, sizeof(char*));
  int i = 0;
  char* ptr = strtok(text," .");
  while(ptr != NULL){
    words[i++] = ptr;
        if(i == words_num) {
          words_num*=2;
          words = realloc(words, words_num*sizeof(char*));
        }
        ptr = strtok(NULL," .");
  }

  qsort(words, i, sizeof(char**), cmp);
  char** ptr_str;
  ptr_str = bsearch(&str, words, i, sizeof(char**), cmp);
  if(ptr_str != NULL)
    printf("exists\n");
  else
    printf("doesn't exist\n");
    
  free(words);
  free(text);
  free(str);
  
  return 0;
}
