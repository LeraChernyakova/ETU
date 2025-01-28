#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include "struct.h"

int is_date(wchar_t* ptr){
  if (wcslen(ptr)<10) 
    return 0;
  int k = 0, i;
  for (i = 0; i <10; i++){
    if (isdigit(ptr[i]))
      k++;
  }
  if ((k==8) && ((ptr[2]==L'/' && ptr[5]==L'/') || (ptr[4]==L'-' && ptr[7]==L'-')))
    return 1;
  return 0;
}

void get_date(wchar_t* ptr, int* year, int* month, int* day){
  if (ptr[2] == L'/'){ 
    *day = (ptr[0] - L'0') * 10 + ptr[1] - L'0';
    *month = (ptr[3] - L'0') * 10 + ptr[4] - L'0';
    *year = (ptr[6] - L'0') * 1000 + (ptr[7] - L'0') * 100 + (ptr[8] - L'0') * 10 + ptr[9] - L'0';
  } 
  else { 
    *day = (ptr[8] - L'0') * 10 + ptr[9] - L'0';
    *month = (ptr[5] - L'0') * 10 + ptr[6] - L'0';
    *year = (ptr[0] - L'0') * 1000 + (ptr[1] - L'0') * 100 + (ptr[2] - L'0') * 10 + ptr[3] - L'0';
  }
}

int cmp(const void * a, const void * b){
  struct My_date *first = (struct My_date*) a;
  struct My_date *second = (struct My_date*) b;
  if (first->year == second->year && first->month == second->month && first->day == second->day)
    return 0;
  return (first->year*10000 + first->month*100 + first->day - (second->year*10000 + second->month*100 + second->day));
}

void sort_date(wchar_t* ptr){
  int max_amount = 20;
  int real_amount = 0;
  struct My_date* ptr_date;
  ptr_date = malloc(max_amount*sizeof(struct My_date));
  
  int i, j, d, m, y;
  
  if (wcslen(ptr) < 10)
    return; 

  for (i = 0; i < wcslen(ptr)-10; i++){
    if (is_date(&ptr[i])){
      get_date(&ptr[i], &y, &m, &d);
      if (real_amount == max_amount){
        max_amount *= 2;
        ptr_date = realloc(ptr_date, max_amount*sizeof(struct My_date));
      }
      ptr_date[real_amount].year = y;
      ptr_date[real_amount].month = m;
      ptr_date[real_amount].day = d;
      wcsncpy(ptr_date[real_amount].src, &ptr[i], 10);
      ptr_date[real_amount].src[10] = L'\0';
      real_amount++;
    }
  }
  qsort(ptr_date, real_amount, sizeof(struct My_date), cmp);
  for (i = 0; i < real_amount; i++)
    printf("%ls\n", ptr_date[i].src);
  free(ptr_date);
}

void display_date(struct Text* text){
  int i, k = 0;
  for (i =0; i < text->real_amount; i++){
    k += text->lines[i]->size;
  }
  wchar_t* buf = malloc(k*sizeof(wchar_t));
  buf[0] = L'\0';
  for (i =0; i < text->real_amount; i++)
    wcscat(buf, text->lines[i]->sent);
  sort_date(buf);
  free(buf);
}

wchar_t* settime(struct tm *a){
  wchar_t s[11];
  wchar_t* tmp;
  s[0] = 0;
  int length = wcsftime(s, 11, L"%d.%m.%Y", a);
  tmp = (wchar_t*) malloc(sizeof(s));
  wcscpy(tmp, s);
  return(tmp);
}

void h_nh(struct Text* text){
  struct tm *today;
  const time_t timer = time(NULL);
  today = localtime(&timer);

  int sym;
  int year, day;
  wchar_t month[4];
  wchar_t* date, *date3;
  for(int i = 0; i < text->real_amount; i++) {
    for (int j = 0; j < text->lines[i]->size; j++){
      sym = text->lines[i]->sent[j];
      if (isdigit(sym)){
        if (isalpha(text->lines[i]->sent[j+4])){
          date = malloc(11*sizeof(wchar_t));
          wcsncpy(date, &text->lines[i]->sent[j], 11);
          if((swscanf(date, L"%2d %3ls %4d", &day, month, &year)) == 3){
            month[3] = L'\0';
            int month_name =  !wcscmp(month, L"Jan") ? 0 : !wcscmp(month, L"Feb") ? 1 : !wcscmp(month, L"Mar") ? 2 : !wcscmp(month, L"Apr") ? 3 : !wcscmp(month, L"May") ? 4 : !wcscmp(month, L"Jun") ? 5 : !wcscmp(month, L"Jul") ? 6 : !wcscmp(month, L"Aug") ? 7 : !wcscmp(month, L"Sep") ? 8 : !wcscmp(month, L"Oct") ? 9 : !wcscmp(month, L"Nov") ? 10 : 11;
            struct tm date2 = {0};          
            date2.tm_year = year-1900;
            date2.tm_mon = month_name;         
            date2.tm_mday = day;
            time_t t_date = mktime(&date2);
            date3 = settime(&date2);

            if (t_date < timer)
              printf("%ls Happened\n", date3);
            if (t_date > timer)
              printf("%ls Not happened\n", date3);
          }
        }
        j += 10;
        continue;
        free(date);
      }
    }
  }
}

 
