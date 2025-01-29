CC = g++

all: scalable strassen main post_clean


scalable: main_scalable.o tasks_generator.o matrix.o scalable_resolver.o
	$(CC) main_scalable.o tasks_generator.o matrix.o scalable_resolver.o -o ex_scalable


strassen: main_strassen.o tasks_generator.o matrix.o strassen_resolver.o
	$(CC) main_strassen.o tasks_generator.o matrix.o strassen_resolver.o -o ex_strassen


main: main.o tasks_generator.o matrix.o scalable_resolver.o strassen_resolver.o
	$(CC) main.o tasks_generator.o matrix.o scalable_resolver.o strassen_resolver.o -o ex_main


main_scalable.o: main_scalable.cpp
	$(CC) -c ./main_scalable.cpp


main_strassen.o: main_strassen.cpp
	$(CC) -c ./main_strassen.cpp


main.o: main.cpp
	$(CC) -c main.cpp


scalable_resolver.o: ./resolvers/scalable_resolver/scalable_resolver.cpp
	$(CC) -c ./resolvers/scalable_resolver/scalable_resolver.cpp


strassen_resolver.o: ./resolvers/strassen_resolver/strassen_resolver.cpp
	$(CC) -c ./resolvers/strassen_resolver/strassen_resolver.cpp


matrix.o: ./matrix/matrix.cpp
	$(CC) -c ./matrix/matrix.cpp


tasks_generator.o: ./tasks_generator/tasks_generator.cpp
	$(CC) -c ./tasks_generator/tasks_generator.cpp


post_clean:
	rm -rf *.o


clean:
	rm -rf *.o ex_scalable ex_strassen ex_main