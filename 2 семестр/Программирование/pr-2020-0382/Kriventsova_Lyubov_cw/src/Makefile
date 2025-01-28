main: main.o first_word.o right_proposal.o reverse.o str_data.o
	gcc main.o first_word.o right_proposal.o reverse.o str_data.o -o main
main.o: main.c
	gcc -c main.c
first_word.o: first_word.c 
	gcc -c first_word.c
right_proposal.o: right_proposal.c 
	gcc -c right_proposal.c
reverse.o: reverse.c 
	gcc -c reverse.c
str_data.o: str_data.c
	gcc -c str_data.c
clean: 
	rm *.o main
