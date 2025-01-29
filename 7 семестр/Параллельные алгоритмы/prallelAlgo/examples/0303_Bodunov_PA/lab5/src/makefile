output: output/main.o output/mandelbrot.o
	g++ output/main.o output/mandelbrot.o -lOpenCL -o output/output.out

output/main.o: main.cpp
	g++ -c main.cpp -lOpenCL -o output/main.o

output/mandelbrot.o: mandelbrot.cpp
	g++ -c mandelbrot.cpp -lOpenCL -o output/mandelbrot.o

clean:
	rm output/*

run:
	output/output.out