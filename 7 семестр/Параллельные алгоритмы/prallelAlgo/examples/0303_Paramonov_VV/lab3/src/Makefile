output: output/main.o output/threads_stage_sep.o output/matrix.o 
	g++ output/main.o output/threads_stage_sep.o output/matrix.o -o output/output.out

output/main.o: main.cpp utils/threads_queue/base_threads_queue.h utils/threads_queue/rough_threads_queue.h utils/threads_queue/thin_threads_queue.h utils/threads_queue/non_lock_threads_queue.h
	g++ -c main.cpp -o output/main.o

output/threads_stage_sep.o: tasks/threads_stage_sep.cpp tasks/threads_stage_sep.h
	g++ -c tasks/threads_stage_sep.cpp -o output/threads_stage_sep.o

output/matrix.o: utils/matrix/matrix.cpp utils/matrix/matrix.h
	g++ -c utils/matrix/matrix.cpp -o output/matrix.o

clean: 
	rm output/*

run:
	output/output.out