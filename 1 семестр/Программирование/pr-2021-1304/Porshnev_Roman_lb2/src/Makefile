all: lb2
lb2: menu.o max.o min.o diff.o sum.o readarr.o
	gcc menu.o max.o min.o diff.o sum.o readarr.o -o menu
menu.o: menu.c max.h min.h diff.h sum.h readarr.h
	gcc -c menu.c
max.o: max.c
	gcc -c max.c
min.o: min.c
	gcc -c min.c
diff.o: diff.c max.h min.h
	gcc -c diff.c 
sum.o: sum.c min.h
	gcc -c sum.c
readarr.o: readarr.c
	gcc -c readarr.c
clean:
	rm -rf *.o lb2
