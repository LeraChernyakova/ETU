menu: menu.o abs_max.o abs_min.o diff.o sum.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu
	
menu.o: menu.c abs_max.h abs_min.h diff.h sum.h
	gcc -c menu.c
	
abs_max.o: abs_max.c abs_max.h
	gcc -c abs_max.c
	
abs_min.o: abs_min.c abs_min.h
	gcc -c abs_min.c
	
diff.o: diff.c abs_max.h abs_min.h diff.h
	gcc -c diff.c
	
sum.o: sum.c abs_max.h abs_min.h diff.h sum.h
	gcc -c sum.c
	
clean:
	rm -rf *.o menu