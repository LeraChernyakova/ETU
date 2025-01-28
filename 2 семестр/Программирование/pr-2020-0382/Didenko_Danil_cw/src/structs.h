#pragma once

typedef struct{
    wchar_t* word;
    int size_word;//Размер слова
    int count_vovels;//Количество гласных
    int up_let;//Начинается ли слово с большой буквы
    int count_equal_words;//Количество одинаковых слов в предложении
    int is_first_rep;//Повторяемое ли слово
}Word;

typedef struct{
    wchar_t* sent;//Хранит указатели на строку предложения
    wchar_t* copy_sent;
    Word* words;
    int size_sent;//Размер предложения
    int index_sent;//Индекс предложения в тексте
    int ind_stop;//Когда заканчивать ввод текста
    int is_begin;//Начало ли предложения
    int spaces;//Количество подряд идущих пробело
    int count_words;//Количество слов в предложении
    wchar_t** masks;//Шаблоны для слов
    int count_mask;//Количество шаблонов
}Sentence;

typedef struct {
    Sentence* text;//Хранит указатель на структуру предложения
    int count_sent;//Количество предложений в тексте
}Text;
