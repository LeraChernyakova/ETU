#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#define buf 4000

int compare(const void * a, const void * b)
{
  const char* aa = *(char**)a;
  const char* bb = *(char**)b;
  long int a1 = atol(aa);
  long int b1 = atol(bb);
  if(a1 > b1) return 1;
  if(a1 < b1) return -1;
  return 0;
}

char** get_text(const char* path, char** text, int* index){
  char s[50];

  FILE* f = fopen(path, "r");
  if(!f){
    return text;
  }

  while(fgets(s, 50, f)){
    strcat(text[*index], s);
  }

  fclose(f);
  return text;
}

char** listDir(const char* path, char** text, int* index){
  char new_path[256] = {0};
  strcpy(new_path, path);
  strcat(new_path, "/");

  DIR* dir = opendir(path);
  if(!dir){
    return text;
  }
  struct dirent* de = readdir(dir);

  while(de){
    if(de->d_type == DT_REG){
      int len = strlen(new_path);
      strcat(new_path, de->d_name);
      get_text(new_path, text, index);
      *index = *index + 1;
      new_path[len] = '\0';
    }

    if((de->d_type == DT_DIR) && strcmp(de->d_name,".") && strcmp(de->d_name,"..")){
      int len = strlen(new_path);
      strcat(new_path, de->d_name);
      listDir(new_path, text, index);
      new_path[len] = '\0';
    }
    de = readdir(dir);
  }

  closedir(dir);
  return text;
}

int main(){
  int index = 0;
  char** text = calloc(buf, sizeof(char*));
  for(int i = 0; i < buf; i++){
    text[i] = calloc(buf, sizeof(char));
  }

  text = listDir("./tests", text, &index);
  qsort(text, index, sizeof(char*), compare);

  FILE* f = fopen("result.txt", "w");
  for(int i = 0; i < index; i++){
    if(text[i][0] != '\0') fprintf(f,"%s\n", text[i]);
  }
  fclose(f);

  for(int i = 0; i < buf; i++){
    free(text[i]);
  }
  free(text);
  return 0;
}
