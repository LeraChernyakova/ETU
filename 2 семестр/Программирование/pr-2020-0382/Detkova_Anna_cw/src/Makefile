all: text
text: text.o del_sent.o less_order.o search.o sort_len_word.o
	gcc text.o del_sent.o less_order.o search.o sort_len_word.o -o text
text.o: text.c
	gcc -c text.c
del_sent.o: del_sent.c
	gcc -c del_sent.c
search.o: search.c
	gcc -c search.c
less_order.o: less_order.c
	gcc -c less_order.c
sort_len_word.o: sort_len_word.c
	gcc -c sort_len_word.c
clean:
	rm *.o text
