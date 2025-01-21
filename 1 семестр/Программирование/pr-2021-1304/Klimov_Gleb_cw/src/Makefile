all: str.o func.o main.o
	gcc str.o func.o main.o -o main
str.o: str.c func.h
	gcc -c str.c
func.o: func.c func.h
	gcc -c func.c
main.o: main.c func.h
	gcc -c main.c
