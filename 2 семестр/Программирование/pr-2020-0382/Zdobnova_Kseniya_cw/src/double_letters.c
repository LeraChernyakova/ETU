#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "double_letters.h"

void double_letters(struct Text text){
    for (int i = 0; i < text.len_text; i++){ //в тексте
        for (int j = 0; j < text.sentences[i].num_of_words; j++){ //в предложении
            int left = 0, right = 1, same = 0;
            while (left < wcslen(text.sentences[i].words[j])){
                if (text.sentences[i].words[j][left] == text.sentences[i].words[j][right]) {
                    right++;
                    same++;
                }
                else {
                    int k = 1;
                    while (k <= same){
                        text.sentences[i].words[j][left + k] = text.sentences[i].words[j][right];
                        k++;
                    }
                    same = 0;
                    left++;
                    right = left + 1;
                }
            }
            if (j == 2){
                text.sentences[i].len_of_3 = wcslen(text.sentences[i].words[j]);
            }
        }
    }
}