all: main.o read_text.o primitiv_func.o write.o anagram.o sort_upper.o one_on_two_char.o swap_word.o
	gcc main.o read_text.o primitiv_func.o write.o anagram.o sort_upper.o one_on_two_char.o swap_word.o  -o  res

main.o: main.c top_header.h read_text.h primitiv_func.h write.h anagram.h sort_upper.h one_on_two_char.h swap_word.h
	gcc -c main.c

read_text.o: read_text.c top_header.h read_text.h
	gcc -c read_text.c

primitiv_func.o: primitiv_func.c top_header.h primitiv_func.h
	gcc -c primitiv_func.c

write.o: write.c top_header.h write.h
	gcc -c write.c 

anagram.o: anagram.c top_header.h anagram.h
	gcc -c anagram.c

sort_upper.o: sort_upper.c top_header.h primitiv_func.h sort_upper.h
	gcc -c sort_upper.c

one_on_two_char.o: one_on_two_char.c top_header.h one_on_two_char.h
	gcc -c one_on_two_char.c

swap_word.o: swap_word.c top_header.h swap_word.h
	gcc -c swap_word.c

clear: 
	rm *.o res

