all: main.o processimage.o printheader.o help.o copy.o flip.o round.o color.o invert.o
	gcc main.o processimage.o printheader.o help.o copy.o flip.o round.o color.o invert.o -o cw -lm

main.o: main.c 
	gcc -c main.c

processimage.o: processimage.c 
	gcc -c processimage.c

printheader.o: printheader.c 
	gcc -c printheader.c

help.o: help.c
	gcc -c help.c

copy.o: copy.c
	gcc -c copy.c

flip.o: flip.c
	gcc -c flip.c

round.o: round.c
	gcc -c round.c

color.o: color.c
	gcc -c color.c

invert.o: invert.c
	gcc -c invert.c

clean:
	rm *.o