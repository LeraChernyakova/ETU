all : menu

menu : menu.o multi_before_and_after_negative.o multi_between_negative.o index_last_negative.c index_first_negative.c
	gcc menu.o multi_before_and_after_negative.o multi_between_negative.o index_last_negative.c index_first_negative.c -o menu

menu.o : menu.c multi_before_and_after_negative.h multi_between_negative.h index_last_negative.h index_first_negative.h
	gcc -c  menu.c 

multi_before_and_after_negative.o: multi_before_and_after_negative.c index_last_negative.h index_first_negative.h
	gcc -c multi_before_and_after_negative.c

multi_between_negative.o: multi_between_negative.c index_last_negative.h index_first_negative.h
	gcc -c multi_between_negative.c

clean:
	rm *.o menu

 

 	
