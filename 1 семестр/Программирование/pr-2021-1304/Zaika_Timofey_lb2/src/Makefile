all: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	gcc menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o -o menu
menu.o: menu.c all_funcs.h
	gcc -c menu.c
index_first_zero.o: index_first_zero.c all_funcs.h
	gcc -c index_first_zero.c
index_last_zero.o: index_last_zero.c all_funcs.h
	gcc -c index_last_zero.c
sum_between.o: sum_between.c all_funcs.h
	gcc -c sum_between.c
sum_before_and_after.o: sum_before_and_after.c all_funcs.h
	gcc -c sum_before_and_after.c
clean:
	rm -r *.o
