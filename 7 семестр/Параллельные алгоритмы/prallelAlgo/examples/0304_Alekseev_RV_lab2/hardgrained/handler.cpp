#include "handler.h"
#include <iostream>
#include <cstring>

Handler::Handler() {

}

void Handler::push(const node& new_node) {
	std::unique_lock<std::mutex> lk(this->mutex);
	this->queue.push(new_node);
	cv.notify_one();
}

void Handler::pop() {
	std::unique_lock<std::mutex> lk(this->mutex);
	
	cv.wait(lk, [this]{return !(this->queue.empty());});
	node last_node = this->queue.front();
	this->queue.pop();
	
	lk.unlock();
	
	this->handle(last_node);
}

void Handler::handle(const node& this_node) {
	int result[MAT_Y][MAT_X];
	memset(result, 0, sizeof(result));

	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < MAT_X; x++) {
			for(int i = 0; i < MAT_N; i++) {
				result[y][x] += this_node.left[y][i] * this_node.right[i][x];
			}
		}
	}

	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < MAT_X; x++) {
			std::cout << result[y][x] << " ";
		}
		std::cout << std::endl;
	}
}


