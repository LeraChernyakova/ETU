output: output/main.o output/threads_mul_lab1.o output/threads_scalable_mul.o output/threads_mul_strassen.o output/matrix.o
	g++ output/main.o output/threads_mul_lab1.o output/threads_scalable_mul.o output/threads_mul_strassen.o output/matrix.o -o output/output.out

output/main.o: main.cpp
	g++ -c main.cpp -o output/main.o

output/threads_mul_lab1.o: multiply/threads_mul_lab1.cpp multiply/multiply.h
	g++ -c multiply/threads_mul_lab1.cpp -o output/threads_mul_lab1.o

output/threads_scalable_mul.o: multiply/threads_scalable_mul.cpp multiply/multiply.h
	g++ -c multiply/threads_scalable_mul.cpp -o output/threads_scalable_mul.o

output/threads_mul_strassen.o: multiply/threads_mul_strassen.cpp multiply/multiply.h
	g++ -c multiply/threads_mul_strassen.cpp -o output/threads_mul_strassen.o

output/matrix.o: utils/matrix.cpp utils/matrix.h
	g++ -c utils/matrix.cpp -o output/matrix.o

clean: 
	rm output/*

run:
	output/output.out