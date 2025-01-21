all: lab2

lab2: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	gcc menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o -o menu

menu.o: menu.c sum_before_and_after.h sum_between.h index_last_zero.h index_first_zero.h
	gcc -c -std=c99 menu.c

index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c -std=c99 index_first_zero.c

index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c -std=c99 index_last_zero.c

sum_between.o: sum_between.c sum_between.h index_last_zero.h index_first_zero.h
	gcc -c -std=c99 sum_between.c

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h sum_between.h index_last_zero.h index_first_zero.h
	gcc -c -std=c99 sum_before_and_after.c

clean:
	rm -rf *.o lab2
