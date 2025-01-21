all: menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o
	gcc index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o -o menu

menu.o: menu.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c menu.c

index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.c


index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c


multi_between_negative.o: multi_between_negative.c multi_between_negative.h index_last_negative.h index_first_negative.h 
	gcc -c multi_between_negative.c


multi_before_and_after_negative.o: index_multi_before_and_after_negativeast_negative.c index_multi_before_and_after_negativeast_negative.h  index_first_negative.h index_last_negative.h 
	gcc -c multi_before_and_after_negative.c
