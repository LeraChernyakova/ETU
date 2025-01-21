all: menu.o multi_before_and_after_negative.o multi_between_negative.o index_last_negative.o index_first_negative.o
	gcc menu.o multi_before_and_after_negative.o multi_between_negative.o index_last_negative.o index_first_negative.o -o menu
menu.o: menu.c multi_before_and_after_negative.h multi_between_negative.h index_last_negative.h index_first_negative.h
	gcc -c menu.c
mba.o: multi_before_and_after_negative.c multi_before_and_after_negative.h index_last_negative.h index_first_negative.h
	gcc -c multi_before_and_after_negative.c
mb.o: multi_between_negative.c multi_between_negative.h index_last_negative.h index_first_negative.h
	gcc -c multi_between_negative.c
ln.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c
fn.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.h
clean:
	rm -rf *.o menu