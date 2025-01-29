all: build

build: main.cpp ocl_matrices_multiplication.cpp ocl_matrices_multiplication.h
	g++ main.cpp ocl_matrices_multiplication.cpp -o mat_mult -lOpenCL

clean:
	@rm -f mat_mult

.PHONY: all build clean
