#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* sentence(){
    int size_s = 180;
    int index = 0;
    char* sent;
    char c = 'f';
    sent = malloc(size_s*sizeof(char));
    while(c != '.' && c != ';' && c != '?' && c != '!'){
      c = getchar();
      sent[index] = c;
      index++;
      if(index == size_s){
        size_s += 50;
        sent = realloc(sent, size_s);
      }
    }
    while(sent[0] == ' ' || sent[0] == '\t' || sent[0] == '\n'){
      for(int i = 0; i < index-1; i++){
        sent[i] = sent[i+1];
      }
      sent[index-1] = '\0';
    }
    return sent;
}


int seven(char* sent){
  for(int i = 0; i < strlen(sent); i++){
    if(sent[i] == '7'){
      return 1;
    }
  }
  return 0;
}

int main()
{
    char** text;
    int size_t = 20;
    int sent_before = 0;
    int sent_after = 0;
    char* sent;
    text = malloc(size_t*sizeof(char*));
    while(1){
      sent = sentence();
      sent_before++;
      if(seven(sent)){
        free(sent);
      }
      else{
        text[sent_after] = sent;
        sent_after++;
        if(!strcmp(text[sent_after-1],"Dragon flew away!")){
          break;
        }
      }
      if(sent_after == size_t){
        size_t += 20;
        text = realloc(text, size_t*sizeof(char*));
      }
    }
    for(int k = 0; k < sent_after ; k++)
        printf("%s\n",text[k]);
    printf("Количество предложений до %d и количество предложений после %d", sent_before - 1, sent_after-1);
    for(int j = 0; j < sent_after ; j++){
        free(text[j]);
    }
    free(text);
    return 0;
}
