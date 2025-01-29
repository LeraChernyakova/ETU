CC = g++

all: matrix_generator processes threads parallel post_clean


matrix_generator: main_matrix_generator.o matrix_generator.o
	$(CC) main_matrix_generator.o matrix_generator.o -o ex_matrix_generator


processes: main_processes.o matrix_reader.o result_writer.o
	$(CC) main_processes.o matrix_reader.o result_writer.o -o ex_processes


threads: main_threads.o matrix_reader.o result_writer.o
	$(CC) main_threads.o matrix_reader.o result_writer.o -o ex_threads


parallel: main_parallel.o matrix_reader.o result_writer.o
	$(CC) main_parallel.o matrix_reader.o result_writer.o -o ex_parallel


main_processes.o: main_processes.cpp
	$(CC) -c main_processes.cpp


main_threads.o: main_threads.cpp
	$(CC) -c main_threads.cpp


main_parallel.o: main_parallel.cpp
	$(CC) -c main_parallel.cpp


matrix_reader.o: matrix_reader/matrix_reader.cpp
	$(CC) -c matrix_reader/matrix_reader.cpp


result_writer.o: result_writer/result_writer.cpp
	$(CC) -c result_writer/result_writer.cpp


main_matrix_generator.o: main_matrix_generator.cpp
	$(CC) -c main_matrix_generator.cpp


matrix_generator.o: matrix_generator/matrix_generator.cpp
	$(CC) -c matrix_generator/matrix_generator.cpp


post_clean:
	rm -rf *.o

clean:
	rm -rf *.o ex_processes ex_threads ex_parallel ex_matrix_generator data/first_multiplier.txt data/second_multiplier.txt data/result.txt 