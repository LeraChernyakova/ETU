all: obj obj/menu.o obj/max.o obj/min.o obj/diff.o obj/sum.o
	gcc obj/menu.o obj/max.o obj/min.o obj/diff.o obj/sum.o -o menu
obj:
	mkdir obj
obj/menu.o: menu.c
	gcc -c menu.c -o obj/menu.o
obj/max.o: assets/max.c
	gcc -c assets/max.c -o obj/max.o
obj/min.o: assets/min.c
	gcc -c assets/min.c -o obj/min.o
obj/diff.o: assets/diff.c
	gcc -c assets/diff.c -o obj/diff.o
obj/sum.o: assets/sum.c
	gcc -c assets/sum.c -o obj/sum.o
clear:
	rm -r obj
clear-w:
	rd obj /s/q