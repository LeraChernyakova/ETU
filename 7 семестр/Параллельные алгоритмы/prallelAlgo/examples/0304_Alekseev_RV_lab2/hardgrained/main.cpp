#include "handler.h"
#include <thread>

#define PROD_AMOUNT_THREADS 1000
#define CONC_AMOUNT_THREADS 1000
#define AMOUNT_TASKS 10000

void pusher(Handler& handler) {
	for(int l = 0; l < AMOUNT_TASKS / PROD_AMOUNT_THREADS; l++) {
		node new_node;

		int j = 1;
		for(int y = 0; y < MAT_Y; y++) {
			for(int x = 0; x < MAT_N; x++) {
				new_node.left[y][x] = j;
				j++;
			}
		}

		j = 1;
		for(int y = 0; y < MAT_N; y++) {
			for(int x = 0; x < MAT_X; x++) {
				new_node.right[y][x] = j;
				j++;
			}
		}

		handler.push(new_node);
	}
}

void poper(Handler& handler) {
	for(int j = 0; j < AMOUNT_TASKS / CONC_AMOUNT_THREADS; j++) {
		handler.pop();
	}
}

int main() {
	Handler handler;
	std::vector<std::thread> prod_threads(PROD_AMOUNT_THREADS);
	std::vector<std::thread> conc_threads(CONC_AMOUNT_THREADS);

	for(int i = 0; i < PROD_AMOUNT_THREADS; i++) {
		prod_threads[i] = std::thread(pusher, std::ref(handler));
	}
	for(int i = 0; i < CONC_AMOUNT_THREADS; i++) {
		conc_threads[i] = std::thread(poper, std::ref(handler));
	}

	for(int i = 0; i < PROD_AMOUNT_THREADS; i++) {
		prod_threads[i].join();
	}
	for(int i = 0; i < CONC_AMOUNT_THREADS; i++) {
		conc_threads[i].join();
	}
}
