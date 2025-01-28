#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "struct.h"
#include "in_n_out.h"
#include "changes.h"
#include "date.h"

int main(){
  setlocale(LC_ALL, "");
  struct Text* text;
  printf("Please enter your text:\n");
  text = read_text();
  show_text(text);

  printf("\nPlease choose one of next actions:\n1. Change substrings; \n2. Display dates; \n3. Delete sentences; \n4. Happened / Not Happened; \n5. Quit program.\nAction: ");

  int action;
  wscanf(L"%d", &action);
  while (action != 5){
    switch (action){
        case 1: 
          change_substrings(text);
          show_text(text);
          break;
        case 2:
          display_date(text);
          break;
        case 3:
          delete_lines(text);
          show_text(text);
          break;
        case 4: 
          h_nh(text);
          break;
        default:
          printf("Invalid action\n");
    }
    printf("Action: ");
    wscanf(L"%d", &action);
  }
  for(int i = 0; i < text->real_amount; i++)
    free(text->lines[i]);
  free(text->lines);
  free(text);
}
