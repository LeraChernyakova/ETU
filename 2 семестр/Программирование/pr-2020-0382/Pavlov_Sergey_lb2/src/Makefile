menu: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	gcc menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o -o menu
menu.o: menu.c
	gcc -std=c99 -c menu.c
index_first_zero.o: index_first_zero.c 
	gcc -std=c99 -c index_first_zero.c
index_last_zero.o: index_last_zero.c 
	gcc -std=c99 -c index_last_zero.c
sum_between.o: sum_between.c 
	gcc -std=c99 -c sum_between.c
sum_before_and_after.o: sum_before_and_after.c
	gcc -std=c99 -c sum_before_and_after.c
clean: 
	rm *.o menu