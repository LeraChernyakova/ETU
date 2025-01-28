all: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	gcc menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o -o menu
menu.o: menu.c index_first_zero.c index_last_zero.c sum_between.c sum_before_and_after.c
	gcc -c menu.c -std=c99
index_first_zero.o: index_first_zero.c
	gcc	-c index_first_zero.c -std=c99
index_last_zero.o: index_last_zero.c
	gcc -c index_last_zero.c -std=c99
sum_between.o: index_first_zero.c index_last_zero.c
	gcc -c sum_between.c -std=c99
sum_before_and_after.o: index_first_zero.c index_last_zero.c
	gcc -c sum_before_and_after.c -std=c99
