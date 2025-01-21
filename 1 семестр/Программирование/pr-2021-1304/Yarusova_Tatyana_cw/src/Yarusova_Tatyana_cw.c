#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* read_sentence(char sep){
    char* sentence;
    int count_char = 0;
    int memory_for_char = 50;
    char c;
    char* t = malloc(memory_for_char * sizeof(char));
    if (t != NULL){
        sentence = t;
    }
    else{
        puts("Ошибка! Недостаточно памяти!");
        return NULL;
    }
    do{

        if (count_char == memory_for_char){
    		memory_for_char += 10;
            t = realloc(sentence, memory_for_char * sizeof(char));
            if(t != NULL){
    		    sentence = t;
            }
            else{
                puts("Ошибка! Недостаточно памяти!");
                return NULL;
            }
    	}

        c = getchar();
        if ((c != '\t') && (c != ' ')){
            sentence[count_char++] = c;
        }
        else{
            if ((c == ' ') && (count_char != 0)){
                sentence[count_char++] = c;   
            }
        }

    }while(sentence[count_char-1] != sep);
    sentence[count_char] = '\0';
    return sentence;
}

int read_text(char*** text, char sep){

    int count_sentence = 0;
    int memory = 10;
    char* sentence;
    char** t = malloc(memory*sizeof(char*)); 
    if(t != NULL){
        *text = t ;
    }
    else{
        puts("Ошибка! Недостаточно памяти!");
        return 0;
    }
     
    do{ 
        sentence = read_sentence(sep);
        (*text)[count_sentence++] = sentence;
        
        if (count_sentence == memory){
    		memory += 10;
            t = realloc(*text, memory * sizeof(char*));
            if (t != NULL){
    		    *text = t; 
    		}
            else{
                puts("Ошибка! Недостаточно памяти!");
                return 0;
            }
        }

    }while(getchar() != '\n');
    return count_sentence;
}

int delete_sentence(char** text, int len){
    int sent = 0;
    int len_before = len;
    while(sent < len - 1){
        int old_len = len;
        int len_sent = strlen(text[sent]);
        int sent2 = sent +1;
        while(sent2 < len){       
            int len_sent2 = strlen(text[sent2]);
            int count_char = 0;
            if(len_sent == len_sent2){
                for(int ch = 0; ch < len_sent;ch++){
                    if((tolower(text[sent][ch]))!= (tolower(text[sent2][ch])))
                        break;
                    else
                        count_char++;  
                }
            }
            if(count_char == len_sent){
                free(text[sent2]);
                len--;
                memmove(text+sent2, text+sent2 + 1, sizeof(char*) * (len - sent2 +1));
            }
            else sent2++;
        }
        if (old_len > len){
            free(text[sent]);
            len--;
            memmove(text+sent, text+sent + 1, sizeof(char*) * (len - sent + 1));  
        }
        else sent++; 
    }
    printf("\nВ тексте было %d повторно встречающихся предложений. Они были удалены!\n", len_before - len);
    return len;
}

void print_garbage(char** text, int len){
    for(int i = 0; i < len; i++){
        int count_garbage = 0;
        int len_sentence = strlen(text[i]);
        if(len_sentence >= strlen("garbage")){
            for(int j = 0; j <= len_sentence - strlen("garbage"); j++){
                if ((tolower(text[i][j])== 'g')&&(tolower(text[i][j+1])== 'a')&&(tolower(text[i][j+2])== 'r')&&(tolower(text[i][j+3])== 'b')
                &&(tolower(text[i][j+4])== 'a')&&(tolower(text[i][j+5])== 'g')&&(tolower(text[i][j+6])== 'e')){
                    count_garbage++;
                }
            }
            if(count_garbage > 0){
                if(count_garbage < 6)
                    puts("Must be washed");
                else
                    puts("It is a dump");

            }
            else
                puts("Clean");
        }
        else
            puts("Clean");
    }

}

void number_string(char** text, int len){
    int memory = 10;
    int count_char = 0;
    char* string;
    char* t = malloc(memory * sizeof(char));
    if(t != NULL){
        string = t;
    }
    else{
        puts("Ошибка! Недостаточно памяти!");
    }
    char c;
    c = getchar();
    do{
        if (memory == count_char){
            memory += 5;
            t = realloc(string, memory * sizeof(char));
            if(t != NULL){
                string = t;
            }
            else{
                puts("Ошибка! Недостаточно памяти!");
            }
        }
        c = getchar();
        if(c != '\n'){
            string[count_char++] = c;
        }
    }while(c != '\n');
    

    for(int sent = 0; sent < len; sent++){
        int count_num = 0;
        int len_sent = strlen(text[sent]);

        for (int i = 0; i < len_sent; i++){
            if(isdigit(text[sent][i]))
                count_num++;
        }

        if(count_num != 0){
            char* m = malloc(len_sent*sizeof(char));
            char* sentence;
            if(m != NULL){
                sentence = m;
            }
            else{
                puts("Ошибка! Недостаточно памяти!");
            }
            strcpy(sentence, text[sent]);
            char* l = realloc(text[sent],((len_sent+count_num * (strlen(string)-1))* sizeof(char)));
            if (l != NULL){
                text[sent] = l;
            }
            else{
                puts("Ошибка! Недостаточно памяти!");
            }
            int i = 0;
            int n = 0;
            while(i < (len_sent + (strlen(string)-1)*count_num)){
                if(isdigit(sentence[n])){
                    for(int k = i, j = 0; j <= strlen(string); k++, j++){
                        text[sent][k] = string[j];
                        
                    }
                    n++;
                    i += strlen(string);
                }
                else{
                    text[sent][i++] = sentence[n++];

                }
           
            free(sentence);
            
        }
        
                    
    }
    free(string);
    
}

int up(char** text, int len){
    int sentence = 0;
    while(sentence < len){
        int flag = 0;
        int len_sentence = strlen(text[sentence]);
        for(int j = 0; j < len_sentence - 2; j++){
            if((isupper(text[sentence][j]))&& (isupper(text[sentence][j+1])) && (isupper(text[sentence][j+2]))){
                flag = 1;
            }
        }
        if(flag){
                free(text[sentence]);
                len--;
                memmove(text+sentence, text+sentence+1, sizeof(char*) * (len-sentence+1));
        }
        else{
            sentence++;
        }
    }
    return len;        
}
int test_vowel(char symbol){
    if((tolower(symbol)=='a') || (tolower(symbol)=='i') ||(tolower(symbol)=='o') || (tolower(symbol)=='e') ||(tolower(symbol)=='y') || (tolower(symbol)=='u'))
        return 1;
    else
        return 0;
}

void vowel(char** text, int len){
    int count_vowel[len];
    for(int sentence = 0; sentence < len; sentence++){
        int count = 0;
        int len_sentence = strlen(text[sentence]) - 1;
        for(int ch = 0; ch < len_sentence - 1; ch++){
            if(((text[sentence][ch]==' ') && (test_vowel(text[sentence][ch+1]))) || (ch == 0) && (test_vowel(text[sentence][ch]))){
                count++;
            }
        }
        count_vowel[sentence] = count;
        
    }
    
    int buff_count;
    char* buff_sent;
    for(int i = len-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(count_vowel[j] < count_vowel[j+1]){
                buff_sent = text[j];
                text[j] = text[j+1];
                text[j+1] = buff_sent;

                buff_count = count_vowel[j];
                count_vowel[j] = count_vowel[j+1];
                count_vowel[j+1] = buff_count;

            }   
        }
    }
}


void print_text(char** text, int sentence){

    for(int i = 0; i < sentence; i++){
        printf("%s ",text[i]);
    }
    printf("\n\n");
}

void free_memory(char*** text, int sentence){

    for(int i = 0; i < sentence; i++){
        free((*text)[i]);
    }

    free((*text));

}

int main(){
    char** text;
    char sep = '.';
    puts("Добро пожаловать!");
    puts("Введите текст, который хотите обработать.");
    int len = read_text(&text, sep);
    len = delete_sentence(text, len); 
    print_text(text,len);
    while (1){
        puts("Как вы хотите обработать текст?");
        puts("1)Вывести количество слов ""garbage"" в каждом предложении.");
        puts("2)Заменить все цифры на введеную вами строку.");
        puts("3)Удалить предложения, в которых встречаются три подряд идущие буквы в верхнем регистре.");
        puts("4)Отсортировать по уменьшению количества слов начинающихся с гласной буквы.");
        puts("5)Завершить программу.");
        printf("Введите номер команды: ");
        int value;
        scanf("%d", &value);
        switch (value){
            case 1:
                puts("\nРезультат:");
                print_garbage(text,len);
                printf("\n");
                break;

            case 2:
                puts("\nВведите строку");
                number_string(text, len);
                puts("\nРузультат:");
                print_text(text,len);
                break;

            case 3: 
                len = up(text, len);
                puts("\nРузультат:");
                print_text(text,len);
                break;                                          

            case 4:
                puts("\nРузультат:");
                vowel(text,len);
                print_text(text,len);
                break;
        
            case 5:
                puts("\nВсего доброго! До свидания!");
                free_memory(&text,len);
                return 0;
            
            default:
                puts("\nВы ввели некорректное значение. Попробуйте еще раз!\n");

        }
    }
}