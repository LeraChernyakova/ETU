CC = gcc

all: menu

menu: menu.o user_choice.o sum_before_and_after.o sum_between.o index_last_zero.o index_first_zero.o read_arr.o
	$(CC) menu.o user_choice.o sum_before_and_after.o sum_between.o index_last_zero.o index_first_zero.o read_arr.o -o menu

menu.o: menu.c user_choice.h read_arr.h
	$(CC) -c menu.c

user_choice.o: user_choice.c user_choice.h sum_before_and_after.h sum_between.h index_last_zero.h index_first_zero.h
	$(CC) -c user_choice.c

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h index_last_zero.h index_first_zero.h
	$(CC) -c sum_before_and_after.c

sum_between.o: sum_between.c sum_between.h index_last_zero.h index_first_zero.h
	$(CC) -c sum_between.c

index_last_zero.o: index_last_zero.c index_last_zero.h
	$(CC) -c index_last_zero.c

index_first_zero.o: index_first_zero.c index_first_zero.h
	$(CC) -c index_first_zero.c

read_arr.o: read_arr.c read_arr.h
	$(CC) -c read_arr.c

clean:
	rm -rf *.o menu
