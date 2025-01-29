output: output/main.o output/Matrix.o
	g++ output/main.o output/Matrix.o -lOpenCL -o output/output.out

output/main.o: main.cpp
	g++ -c main.cpp -lOpenCL -o output/main.o

output/Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp -lOpenCL -o output/Matrix.o

clean:
	rm output/*

run:
	output/output.out