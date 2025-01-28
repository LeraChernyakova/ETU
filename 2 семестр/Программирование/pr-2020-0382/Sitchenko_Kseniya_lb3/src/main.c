#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_line(){
  int memory = 100;
  int line_length = 0;
  int sym, fl = 1;
  char *line = malloc(memory *sizeof(char));
  while (1) {
    sym = getchar();
    if (fl == 1 && (sym == ' '|| sym == '\t' || sym == '\n'))
      continue;
    else
      fl = 0;
    line[line_length++] = sym;
    if (sym == '.' || sym == ';' || sym == '?' || sym == '!') 
      break;
    if (line_length == memory) {
      memory += 100;
      line = realloc(line, memory);
    } 
  }
  line[line_length] = '\0';
  return line;
}

int has_qm (char* line){
  int qm = 0;
  if (line[strlen(line)-1] == '?') 
    qm = 1;
  return qm;
}

int main() {
  int text_lenght = 0; 
  int qm_amount = 0;
  int memory = 100;
  char* stop_line = "Dragon flew away!";
  char** text = malloc(memory*sizeof(char*));
  char* line;
  while (1) {
    line = get_line();
    if (!has_qm(line))
      text[text_lenght++] = line;
    else qm_amount += 1;
    if (text_lenght == memory) {
      memory += 100;
      text = realloc(text, memory*sizeof(char*));
    }
    if (!strcmp(line, stop_line)) break;
  }
  
  for (int i = 0; i < text_lenght; i++){
      puts(text[i]);
      free(text[i]);
    }
  free(text);
  printf("Количество предложений до %d и количество предложений после %d\n", text_lenght+qm_amount-1, text_lenght-1);
  return 0;
}

