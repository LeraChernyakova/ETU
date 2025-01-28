all: menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o
	gcc menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o -o menu -std=c99
menu.o: menu.c index_first_even.h index_last_odd.h sum_between_even_odd.h sum_before_even_and_after_odd.h
	gcc -c menu.c -std=c99
index_first_even.o: index_first_even.c index_first_even.h
	gcc -c index_first_even.c -std=c99
index_last_odd.o: index_last_odd.c index_last_odd.h
	gcc -c index_last_odd.c -std=c99
sum_between_even_odd.o:	sum_between_even_odd.c sum_between_even_odd.h index_first_even.h index_last_odd.h
	gcc -c sum_between_even_odd.c -std=c99
sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c sum_before_even_and_after_odd.h index_first_even.h index_last_odd.h
	gcc -c sum_before_even_and_after_odd.c -std=c99
clean:
	rm *.o menu
