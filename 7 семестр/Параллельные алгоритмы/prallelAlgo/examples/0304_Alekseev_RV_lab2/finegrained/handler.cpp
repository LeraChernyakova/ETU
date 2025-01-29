#include "handler.h"
#include <iostream>
#include <cstring>

Handler::Handler() {
	this->tail_node = new node;
	this->head_node = this->tail_node;
}

void Handler::push(node* new_node) {
	std::unique_lock<std::mutex> lk(this->tail_mutex);
	
	node* newTail = new node;
	memcpy(this->tail_node->left, new_node->left, sizeof(new_node->left));
	memcpy(this->tail_node->right, new_node->right, sizeof(new_node->left));
	this->tail_node->next = newTail;
	this->tail_node = newTail;
	
	cv.notify_one();
}

void Handler::pop() {
	std::unique_lock<std::mutex> lk(this->head_mutex);
	cv.wait(lk, [this]{return this->head_node != this->get_tail();});
	
	node* old_head = this->head_node;
	this->head_node = this->head_node->next;

	lk.unlock();

	this->handle(old_head);
	delete old_head;
}

void Handler::handle(node* this_node) {
	int result[MAT_Y][MAT_X];
	memset(result, 0, sizeof(result));

	for(int y = 0; y < MAT_Y; y++) {
		for(int x = 0; x < MAT_X; x++) {
			for(int i = 0; i < MAT_N; i++) {
				result[y][x] += this_node->left[y][i] * this_node->right[i][x];
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

node* Handler::get_tail() {
	std::unique_lock<std::mutex> lk(this->tail_mutex);
	return this->tail_node;
}


