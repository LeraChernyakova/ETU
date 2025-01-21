all:menu
menu:main.o print_and_input.o decide.o
	gcc main.o print_and_input.o decide.o -o menu
main.o:main.c print_and_input.h decide.h
	gcc -c main.c
print_and_input.o:print_and_input.c print_and_input.h
	gcc -c print_and_input.c
decide.o:decide.c decide.h
	gcc -c decide.c
