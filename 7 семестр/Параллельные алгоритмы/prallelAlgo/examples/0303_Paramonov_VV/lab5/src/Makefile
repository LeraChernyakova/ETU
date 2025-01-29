output: output/main.o output/opencl_handler.o output/utility.o
	g++ output/main.o output/opencl_handler.o output/utility.o -lOpenCL -o output/output.out

output/main.o: main.cpp
	g++ -c main.cpp -lOpenCL -o output/main.o

output/opencl_handler.o: utility/opencl_handler.cpp utility/opencl_handler.hpp
	g++ -c utility/opencl_handler.cpp -lOpenCL -o output/opencl_handler.o

output/utility.o: utility/utility.cpp utility/utility.hpp
	g++ -c utility/utility.cpp -o output/utility.o

clean: 
	rm output/*

run:
	output/output.out