all: main.o shift_words.o unic_symbols.o len_words.o del_up.o processing_entered_text.o
	gcc main.o shift_words.o unic_symbols.o len_words.o del_up.o processing_entered_text.o

main.o: main.c shift_words.h unic_symbols.h len_words.h del_up.h processing_entered_text.h
	gcc -c main.c

shift_words.o: shift_words.c shift_words.h processing_entered_text.h
	gcc -c shift_words.c

unic_symbols.o: unic_symbols.c unic_symbols.h processing_entered_text.h
	gcc -c unic_symbols.c

len_words.o: len_words.c len_words.h processing_entered_text.h
	gcc -c len_words.c

del_up.o: del_up.c del_up.h processing_entered_text.h
	gcc -c del_up.c

clean:
	rm *.o a.out
