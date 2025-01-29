CC = g++

all: lock_free post_clean


lock_free: main.o lock_free_queue.o matrix.o
	$(CC) main.o lock_free_queue.o matrix.o -o ex_lock_free


main.o: main.cpp
	$(CC) -c -latomic ./main.cpp


matrix.o: ./matrix/matrix.cpp
	$(CC) -c ./matrix/matrix.cpp


lock_free_queue.o: ./lock_free_queue/lock_free_queue.cpp
	$(CC) -c ./lock_free_queue/lock_free_queue.cpp


post_clean:
	rm -rf *.o


clean:
	rm -rf *.o ex_fine_grained ex_thread_safe