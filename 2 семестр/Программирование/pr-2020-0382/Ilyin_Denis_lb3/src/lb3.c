#include <stdio.h>
#include <stdlib.h>

int is_equal(char* sent, char* end_sent){

    int flag = 0;
    for (int i = 0;i<17;i++){
        if (sent[i + 1] != end_sent[i]){
            flag = 1;
            break;
        }
    }
    return flag;
}

int text_lengh(char ** mass, char * con){
    int i = 0;
    while(is_equal(mass[i], con)){
        i++;
    }
    i++;
    return i;
}

char* newstr(char* con){
    int step = 100;
    int sent_size = 0;
    char* sent;
    sent = malloc(100 * sizeof(char));
    char input_char = getchar();
    char b;
    if ((input_char != '\t') && (input_char != ' ') && (input_char != '\n')){
        if (sent_size + 10 > step){
            step += 100;
            sent = realloc(sent, step * sizeof(char));
        }
        sent[sent_size] = '\n';
        sent_size++;
    }
    else{
        while ((input_char == '\t') || (input_char == ' ') || (input_char == '\n')){
            input_char = '\n';
            b = getchar();
            if ((b == '\t')||(b == ' ')||(b == '\n')){
                input_char = b;
            }
            else{
                if (sent_size + 10 > step){
                    step += 100;
                    sent = realloc(sent, step * sizeof(char));
                }
                sent[sent_size] = input_char;
                input_char = b;
                sent_size++;
            }
        }
    }
    while ((input_char != '.') && (input_char != ';') && (input_char != '?')){
        if ((input_char == '!') && (~is_equal(sent, con))){
            break;
        }
        else{
            if (sent_size + 10 > step){
                step += 100;
                sent = realloc(sent, step * sizeof(char));
            }
            sent[sent_size] = input_char;
            input_char = getchar();
            sent_size++;
        }
    }
    if (input_char == '?'){
        sent = malloc(2 * sizeof(char));
        sent[0] = '?';
    }
    else{
        if (sent_size + 10 > step){
            step += 100;
            sent = realloc(sent, step * sizeof(char));
        }
        sent[sent_size] = input_char;
    }
    return sent;

}

char ** mass(char ** input, char * con, char * nowstr, int kolstr){
    if (is_equal(nowstr, con)){
        kolstr++;
        input = realloc(input, kolstr * sizeof(char*));
        nowstr = newstr(con);
        input[kolstr - 1] = nowstr;
        return mass(input, con, nowstr, kolstr);
    }
    else{
        input = realloc(input, (kolstr + 1) * sizeof(char*));
        input[kolstr] = con;
        return input;
    }
}

char ** del_sent(char** text, int text_size){
    int i = 0;
    while (i < text_size){
        if (text[i][0] == '?'){
            for (int j = i; j < text_size; ++j){
                text[j] = text[j + 1];
            }
            --text_size;
        }
        else {
            i++;
        }
    }
    return text;
}

int main() {
    char ** input, ** start_text, ** end_text;
    int start_size, end_size;
    int i = 0, j = 0;
    char * input_sent;
    input_sent = malloc(2 * sizeof(char));
    input = malloc(2 * sizeof(char*));
    char * end_sent = "Dragon flew away!";
    start_text = mass(input, end_sent, input_sent, 0);
    start_size = text_lengh(start_text, end_sent);
    end_text = del_sent(start_text, start_size);
    end_size = text_lengh(end_text, end_sent);
    while (is_equal(end_text[i], end_sent)){
        j = 0;
        while ((end_text[i][j] != '.') && (end_text[i][j] != ';')){
            printf("%c", end_text[i][j]);
            j++;
        }
        printf("%c", end_text[i][j]);
        i++;
    }
    printf("\nDragon flew away!\nКоличество предложений до %d и количество предложений после %d", start_size-1, end_size - 1);
    return 0;
}
















