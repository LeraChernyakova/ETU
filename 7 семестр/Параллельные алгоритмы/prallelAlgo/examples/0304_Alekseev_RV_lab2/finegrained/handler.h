#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>

#define MAT_Y 4
#define MAT_N 4
#define MAT_X 4

struct node
{
	int left[MAT_Y][MAT_N];
	int right[MAT_N][MAT_X];
	node* next;
};

class Handler {
public:
	Handler();

	void push(node* new_node);
	void pop();

	void handle(node* this_node);
	node* get_tail();

private:
	std::mutex head_mutex;
	std::mutex tail_mutex;
	
	std::condition_variable cv;

	node* head_node;
	node* tail_node;
};

#endif