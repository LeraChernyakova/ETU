output: output/main.o output/opencl_mul.o output/strassen_mul.o output/opencl_handler.o output/utility.o output/matrix.o
	g++ output/main.o output/opencl_mul.o output/strassen_mul.o output/opencl_handler.o output/utility.o output/matrix.o -lOpenCL -ltbb -o output/output.out

output/main.o: main.cpp
	g++ -c main.cpp -lOpenCL -o output/main.o

output/opencl_handler.o: utility/opencl_handler.cpp utility/opencl_handler.hpp
	g++ -c utility/opencl_handler.cpp -lOpenCL -o output/opencl_handler.o

output/utility.o: utility/utility.cpp utility/utility.hpp
	g++ -c utility/utility.cpp -o output/utility.o

output/matrix.o: utility/matrix.cpp utility/matrix.hpp
	g++ -c utility/matrix.cpp -o output/matrix.o

output/opencl_mul.o: multiply/opencl_mul.cpp multiply/multiply.hpp
	g++ -c multiply/opencl_mul.cpp -lOpenCL -o output/opencl_mul.o

output/strassen_mul.o: multiply/strassen_mul.cpp multiply/multiply.hpp
	g++ -c multiply/strassen_mul.cpp -ltbb -o output/strassen_mul.o

clean: 
	rm output/*

run:
	output/output.out