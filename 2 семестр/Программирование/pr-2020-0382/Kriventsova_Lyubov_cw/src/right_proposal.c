#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "structs.h"
#include "right_proposal.h"
struct Sentence right_proposal(struct Sentence sent){
    int  count = 0;
    for (int i = 0; i < sent.lent; i++){
        if (sent.phrase[i]== L' ' || sent.phrase[i] == L',' || sent.phrase[i] == L'.'){
            if (count>sent.maxword) sent.maxword = count;
            count = 0;
            sent.countwords++;
        }
        else  count++;
    }
    if (sent.maxword>3)  sent.right = 1;
    else  sent.right = 0;
    return sent;
}
