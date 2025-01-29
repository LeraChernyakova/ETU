all: build

build: main.cpp ocl_matrices_multiplication.cpp ocl_matrices_multiplication.h
	g++ main.cpp ocl_matrices_multiplication.cpp -o matrices_multiplication -lOpenCL

clean:
	@rm -f matrices_multiplication

.PHONY: all build clean
