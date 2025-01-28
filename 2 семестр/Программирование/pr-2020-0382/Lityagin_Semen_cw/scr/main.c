#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//-------<Ввод предложений>-----------------------------------------------------

char* sentence(){
    int size_s = 180;
    int index = 0;
    char* sent;
    char c = 'f';
    sent = calloc(size_s, sizeof(char));
    while(c != '.'){
        c = getchar();
        sent[index] = c;
        index++;
        if(c == '\0'){
            break;
        }
        if(index == size_s){
            size_s += 50;
            sent = realloc(sent, size_s);
        }
    }
    return sent;
}

//-------<Удаление пробелов, табуляций, переносов строк в начале предложения>---

char* delete_space(char* sent){
    while(sent[0] == ' ' || sent[0] == '\t' || sent[0] == '\n'){
        for(int i = 0; i < strlen(sent)-1; i++){
            sent[i] = sent[i+1];
            if (i == strlen(sent) - 2){
                sent[strlen(sent)-1] = '\0';
            }
        }
    }
    return sent;
}

//-------<Удаление повторяющихся предложений>-----------------------------------

char** delete_repeat(char** text, int* sent_before){
    for(int i = 0; i < *sent_before; i++){
      for(int j = i+1; j < *sent_before; j++){
        if(!strcasecmp(text[i], text[j])){
          for(int k = j; k < *sent_before; k++){
              text[k] = text[k+1];
          }
          j--;
          *sent_before = *sent_before -1;
        }
      }
    }
    return text;
}

//-------<Отбор предложений, в которых больше 2 и меньше 7 слов>----------------

char** words(char** text, int* sent_before){
    int spaces = 0;
    for(int i = 0; i < *sent_before-1; i++){
      for(int j = 0; j < strlen(text[i]); j++){
        if(text[i][j] == ' '){
          spaces ++;
        }
      }
      if (spaces < 2 || spaces >=6){
        for(int p = i; p < *sent_before; p++){
          text[p] = text[p+1];
        }
        i--;
        *sent_before = *sent_before - 1;
      }
      spaces = 0;
    }
    return text;
}

//-------<Ввод текста, состоящего из предложений>-------------------------------

char** input(int* sent_before){
    char** text;
    int size_t = 20;
    char* sent;
    text = malloc(size_t*sizeof(char*));
    while(1){
        sent = sentence();
        *sent_before += 1;
        text[*sent_before-1] = delete_space(sent);
        if(sent[strlen(sent)-1]=='\0'){
            break;
        }
        if(*sent_before == size_t-1){
            size_t += 20;
            text = realloc(text, size_t*sizeof(char*));
        }
    }
    return text;
}

//-------<Удаление предложений с кол-вом слов, больше среднего>-----------------

float average_words(char** text, int* sent_before){
  int spaces = 0;
  float words = 0;
  for(int i = 0; i < *sent_before-1; i++){
    for(int j = 0; j < strlen(text[i]); j++){
      if(text[i][j] == ' '){
        spaces ++;
      }
    }
    words = words + spaces + 1;
    spaces = 0;
  }
  words = words/ (*sent_before-1);
  return words;
}

char** delete_less_average_words(char** text, int* sent_before){
    float aver_w = average_words(text, sent_before);
    int spaces = 0;
    int words = 0;
    for(int i = 0; i < *sent_before; i++){
      for(int j = 0; j < strlen(text[i]); j++){
        if(text[i][j] == ' '){
          spaces ++;
        }
      }
      words = spaces +1;
      if (words > aver_w){
        for(int p = i; p < *sent_before; p++){
          text[p] = text[p+1];
        }
        i--;
        *sent_before = *sent_before - 1;
      }
      spaces = 0;
      words = 0;
    }
    return text;
}
//-------<Сортировка по убыванию времени>---------------------------------------

char** sortirovka_time(char** text, int* sent_before){
  int times[*sent_before-1][3];
  int total_time[*sent_before-1];
  for(int i = 0; i < *sent_before -1; i++){
    times[i][0] = 0;
    times[i][1] = 0;
    times[i][2] = 0;
    if(strlen(text[i])-1 >= 8){
      for(int j = 0; j < strlen(text[i])-8; j++){
        if((j >0 && isdigit(text[i][j]) && text[i][j-1] == ' ') || (j == 0 && isdigit(text[i][j]))){
          if(isdigit(text[i][j+1])){
            if(text[i][j+2] == '-'){
              if(isdigit(text[i][j+3])){
                if(isdigit(text[i][j+4])){
                  if(text[i][j+5] == '-'){
                    if(isdigit(text[i][j+6])){
                      if(isdigit(text[i][j+7])&& (text[i][j+8] == ' ' || text[i][j+8] == '.'|| text[i][j+8] == ',')){
                        times[i][0] = times[i][0] + (text[i][j+6]-48)*10 + (text[i][j+7]-48);
                        times[i][1] = times[i][1] + (text[i][j+3]-48)*10 + (text[i][j+4]-48);
                        times[i][2] = times[i][2] + (text[i][j]-48)*10 + (text[i][j+1]-48);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    times[i][1] = times[i][1]+times[i][0]/60;
    times[i][2] = times[i][2]+times[i][1]/60;
    times[i][1] = times[i][1]%60;
    times[i][0] = times[i][0]%60;
    total_time[i] = times[i][2]*10000 + times[i][1]*100 + times[i][0];
  }
  int buf = 0;
  char *sent;
  sent = malloc(10*sizeof(char));
  for(int i = 0; i< *sent_before-1; i++){
    for(int j = i; j< *sent_before-1;j++){
      if(total_time[j] > total_time[i]){
        buf = total_time[i];
        total_time[i] = total_time[j];
        total_time[j] = buf;

        sent = realloc(sent, strlen(text[i]));
        strcpy(sent, text[i]);
        strcpy(text[i], text[j]);
        strcpy(text[j], sent);
      }
    }
  }
  return text;
}

//-------<Замена строчных согласных на заглавные согласные>---------------------

char** consonant_up(char** text, int* sent_before){
  char a[20] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'r', 's', 't', 'v', 'w', 'x', 'z'};
  for(int i = 0; i < *sent_before -1; i++){
    for(int j = 0; j< strlen(text[i]); j++){
      for(int k = 0; k<20; k++){
        if(tolower(text[i][j]) == a[k]){
          text[i][j] = toupper(text[i][j]);
        }
      }
    }
  }
  return text;
}

//-------<Output>---------------------------------------------------------------

void output(char** text, int* sent_before){
    for(int i = 0; i<*sent_before-1; i++){
      printf("%s", text[i]);
    }
    printf("\n");
}
//-------<Menu>-----------------------------------------------------------------

void menu(char** text, int* sent_before, int n){
  int k;
  while(1){
    switch(n){
        case 1:
          text = sortirovka_time(text, sent_before);
          output(text, sent_before);
          k = 1;
          break;
        case 2:
          text = words(text, sent_before);
          output(text, sent_before);
          k = 1;
          break;
        case 3:
          text = consonant_up(text, sent_before);
          output(text, sent_before);
          k = 1;
          break;
        case 4:
          text = delete_less_average_words(text, sent_before);
          output(text, sent_before);
          k = 1;
          break;
        case 5:
          k = 2;
          break;
        default:
          printf("Вы ввели недоступное действие. Введите доступное действие.\n");
          break;
      }
    if(k == 1){
      printf("\nВведите выбранный номер действия: ");
      scanf("%d", &n);
    }
    if(k == 2){
      break;
    }
  }
}

//------------------------------------------------------------------------------

int main()
{
    char** text;
    int n;
    int sent_before = 0;
    printf("\tЗдравствуйте, дорогой пользователь!\n");
    printf("Вам доступны следующие действия по обработке текста:\n");
    printf("  1.Отсортировать все предложение по уменьшению суммарного времени указанного в строке.\n");
    printf("  2.Вывести все предложения в которых количество слов больше 2 и меньше 7.\n");
    printf("  3.Во всем тексте заменить согласные строчные буквы на заглавные.\n");
    printf("  4.Удалить все предложения в которых количество слов больше среднего количества слов предложениях.\n");
    printf("  5.Прекращение работы программы.\n");
    printf("Введите ваш текст:\n");
    text = input(&sent_before);
    text = delete_repeat(text, &sent_before);
    printf("\nВведите выбранный номер действия: ");
    scanf("%d", &n);
    menu(text, &sent_before,n);
    for(int j = 0; j < sent_before ; j++){
        free(text[j]);
    }
    free(text);
    return 0;
}
