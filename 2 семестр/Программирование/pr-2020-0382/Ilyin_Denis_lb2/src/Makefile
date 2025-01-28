menu: menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o
	gcc menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o -o menu

menu.o: menu.c index_first_negative.h
	gcc -c menu.c

index_first_negative.o: index_first_negative.c
	gcc -c index_first_negative.c

index_last_negative.o: index_last_negative.c
	gcc -c index_last_negative.c

multi_between_negative.o: multi_between_negative.c
	gcc -c multi_between_negative.c

multi_before_and_after_negative.o: multi_before_and_after_negative.c
	gcc -c multi_before_and_after_negative.c

clean:
	rm -rf *.o menu
