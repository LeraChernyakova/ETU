#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cmp(const void *a, const void *b)
{
  char *fstr = *(char **)a;
  char *sstr = *(char **)b;
  long long int f = atoi(fstr);
  long long int s = atoi(sstr);
  if (f == s)
    return 0;
  if (f > s)
    return 1;
  if (f < s)
    return -1;
}

void add_to_arr(char *string, char **arr, long long int *len)
{
  arr[(*len)++] = string;
}

void writeintotxt(char **arr, long long int *len)
{
  FILE *f = fopen("./result.txt", "w");
  if (f == NULL)
  {
    puts("Error, can't open txt file to write");
    return;
  }
  int i;
  for (i = 0; i < *len; i++)
    fprintf(f, "%s\n", arr[i]);
  fclose(f);
}

char *read_file(char *filename)
{
  FILE *f = fopen(filename, "r"); 
  if (f == NULL)
  {
    puts("Error, can't open txt file to read");
    exit(1);
  }
  char *s = malloc(100 * sizeof(char));
  fgets(s, 100, f);
  fclose(f);
  return s;
}

void list_dir(const char *dirPath, char **arr_of_strs, long long int *len_size)
{
  DIR *dir = opendir(dirPath);
  if (dir == NULL)
  {
    puts("Error, can't open dir");
    return;
  }
  struct dirent *de = readdir(dir);
  while (de)
  {
    if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
    {
      char path[100] = {0};
      strcat(path, dirPath);
      strcat(path, "/");
      strcat(path, de->d_name);
      list_dir(path, arr_of_strs, len_size);
    }
    if (strcmp(de->d_name, "result.txt") != 0 && strstr(de->d_name, ".txt") != NULL)
    {
      char path[100] = {0};
      strcat(path, dirPath);
      strcat(path, "/");
      strcat(path, de->d_name);
      add_to_arr(read_file(path), arr_of_strs, len_size);
    }
    de = readdir(dir);
  }
  closedir(dir);
}

int main()
{
  long long int len_size = 0;
  long long int i;
  char **arr_of_strs = malloc(5000 * sizeof(char *));
  if (arr_of_strs != NULL)
    list_dir(".", arr_of_strs, &len_size);
  qsort(arr_of_strs, len_size, sizeof(char *), cmp);
  writeintotxt(arr_of_strs, &len_size);
  for (i = 0; i < len_size; i++)
    free(arr_of_strs[i]);
  free(arr_of_strs);
  return 0;
}
