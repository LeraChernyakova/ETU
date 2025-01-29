CC = g++

all: thread_safe fine_grained post_clean


thread_safe: thread_safe_main.o thread_safe_queue.o matrix.o
	$(CC) thread_safe_main.o thread_safe_queue.o matrix.o -o ex_thread_safe


fine_grained: fine_grained_main.o fine_grained_queue.o matrix.o
	$(CC) fine_grained_main.o fine_grained_queue.o matrix.o -o ex_fine_grained


matrix.o: ./matrix/matrix.cpp
	$(CC) -c ./matrix/matrix.cpp


thread_safe_main.o: thread_safe_main.cpp
	$(CC) -c thread_safe_main.cpp


fine_grained_main.o: fine_grained_main.cpp
	$(CC) -c fine_grained_main.cpp


thread_safe_queue.o: ./thread_safe_queue/thread_safe_queue.cpp
	$(CC) -c ./thread_safe_queue/thread_safe_queue.cpp


fine_grained_queue.o: ./fine_grained_queue/fine_grained_queue.cpp
	$(CC) -c ./fine_grained_queue/fine_grained_queue.cpp


post_clean:
	rm -rf *.o


clean:
	rm -rf *.o ex_fine_grained ex_thread_safe